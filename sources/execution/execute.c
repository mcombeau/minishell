#include "minishell.h"

/* execute_builtin:
*	Executes the given command if it is a builtin command.
*	Returns -1 if the command is not a builtin command.
*	Returns 0 or 1 if the builtin command succeeded or failed.
*/
static int	execute_builtin(t_command *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = cd_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = echo_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = env_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = exit_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = export_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = pwd_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = unset_builtin(cmd->args);
	return (ret);
}

/* execute_sys_bin:
*	Executes the command's system binary file if it can be found
*	among the environment executable paths.
*	Returns CMD_NOT_FOUND if a path to the executable bin file cannot be
*	found. Returns 1 in case of failure to run existing, executable
*	file.
*/
static int	execute_sys_bin(t_command *cmd)
{
	cmd->path = get_cmd_path(cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, g_env_vars) == -1)
		errmsg("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/* execute_local_bin:
*	Attempts to execute the given command as is, in case
*	it is a local directory file or already contains the
*	path to bin.
*	Returns CMD_NOT_FOUND if the command is not an existing executable
*	file. Returns 1 in case of failure to launch executable.
*/
static int	execute_local_bin(t_command *cmd)
{
	if (access(cmd->command, F_OK | X_OK) != 0)
		return (CMD_NOT_FOUND);
	if (execve(cmd->command, cmd->args, g_env_vars) == -1)
		errmsg("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/* execute_command:
*	Child process tries to execute the given command by setting
*	its input/output fds and searching for an executable.
*	Searching for executable in this order:
*		1. Execute builtin command
*		2. Execute system binaries for command.
*		3. Execute given command name directly (local bin)
*	If it cannot find a matching builtin or executable,
*	prints an error message.
*	Child exits with it's executed program's exit code, or 1 if
*	it could not find one.
*/
static int	execute_command(t_command *cmd_list, t_command *cmd)
{
	int	ret;

	set_pipe_fds(cmd_list, cmd);
	close_fds(cmd_list, false);
	if (!cmd->command)
		exit(errmsg("child process", NULL, "parsing error: no command to execute!", EXIT_FAILURE));
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_builtin(cmd);
		if (ret != CMD_NOT_FOUND)
			exit(ret);
		ret = execute_sys_bin(cmd);
		if (ret != CMD_NOT_FOUND)
			exit(ret);
	}
	ret = execute_local_bin(cmd);
	if (ret != CMD_NOT_FOUND)
		exit(ret);
	exit(errmsg(cmd->command, NULL, "command not found", EXIT_FAILURE));
}

/* get_children:
*	Waits for children to terminate after cleaning up fds and the command
*	list.
*	Returns a child's exit status as bash does:
*		"The return status (see Exit Status) of a simple command is its
*		exit status as provided by the POSIX 1003.1 waitpid function, or
*		128+n if the command was terminated by signal n."
*/
static int	get_children(t_command *cmd_list)
{
	int			status;

	close_fds(cmd_list, false);
	free_cmd_list(cmd_list);
	while (waitpid(-1, &status, 0) != -1 || errno != ECHILD)
		continue ;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

void	debug_print_cmd(t_command *cmd)
{
	int	i;

	printf("Segfault?\n");
	printf("Command to exec: %s\n", cmd->command);
	i = 0;
	while (cmd->args[i] != NULL || cmd->args[i][0] != '\0')
	{
		printf("cmd arg[%d] = %s\n", i, cmd->args[i]);
		i++;
	}
}

/* execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate. If the command is a builtin
*	and its output is not piped to another command, it is not forked.
*	Returns the exit code of the last child to terminate.
*/
int	execute(t_command *cmd_list)
{
	t_command	*cmd;
	int			pid;
	int			ret;

	ret = CMD_NOT_FOUND;
	cmd = cmd_list;
//	debug_print_cmd(cmd);
	if (!create_pipes(cmd_list) || !open_infile_outfile(cmd_list->io_fds))
		return (0);
	pid = -1;
	while (pid != 0 && cmd)
	{
		if (!cmd->pipe_output)
			ret = execute_builtin(cmd);
		if (ret != CMD_NOT_FOUND)
		{
			free_cmd_list(cmd_list);
			return (ret);
		}
		pid = fork();
		if (pid == -1)
			errmsg("fork", NULL, strerror(errno), errno);
		else if (pid == 0)
			execute_command(cmd_list, cmd);
		cmd = cmd->next;
	}
	return (get_children(cmd_list));
}
