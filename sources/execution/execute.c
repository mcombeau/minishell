#include "minishell.h"

int	g_last_exit_code;

/* execute_builtin:
*	Executes the given command if it is a builtin command.
*	Returns -1 if the command is not a builtin command.
*	Returns 0 or 1 if the builtin command succeeded or failed.
*/
static int	execute_builtin(t_data *data, t_command *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = cd_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = echo_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = env_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = exit_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = export_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = pwd_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = unset_builtin(data, cmd->args);
	return (ret);
}

/* execute_sys_bin:
*	Executes the command's system binary file if it can be found
*	among the environment executable paths.
*	Returns CMD_NOT_FOUND if a path to the executable bin file cannot be
*	found. Returns 1 in case of failure to run existing, executable
*	file.
*/
static int	execute_sys_bin(t_data *data, t_command *cmd)
{
	cmd->path = get_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/* execute_local_bin:
*	Attempts to execute the given command as is, in case
*	it is a local directory file or already contains the
*	path to bin.
*	Returns CMD_NOT_FOUND if the command is not an existing executable
*	file. Returns 1 in case of failure to launch executable.
*/
static int	execute_local_bin(t_data *data, t_command *cmd)
{
	if (access(cmd->command, F_OK | X_OK) != 0)
		return (CMD_NOT_FOUND);
	if (execve(cmd->command, cmd->args, data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
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
static int	execute_command(t_data *data, t_command *cmd)
{
	int	ret;

	set_pipe_fds(data->cmd, cmd);
	close_fds(data->cmd, false);
	if (!cmd->command)
		exit(errmsg_cmd("child process", NULL, "parsing error: no command to execute!", EXIT_FAILURE));
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_builtin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit(ret);
		ret = execute_sys_bin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit(ret);
	}
	ret = execute_local_bin(data, cmd);
	if (ret != CMD_NOT_FOUND)
		exit(ret);
	exit(errmsg_cmd(cmd->command, NULL, "command not found", EXIT_FAILURE));
}

/* get_children:
*	Waits for children to terminate after cleaning up fds and the command
*	list.
*	Returns a child's exit status as bash does:
*		"The return status (see Exit Status) of a simple command is its
*		exit status as provided by the POSIX 1003.1 waitpid function, or
*		128+n if the command was terminated by signal n."
*/
static int	get_children(t_data *data)
{
	int			status;

	close_fds(data->cmd, false);
	free_data(data, false);
	while (waitpid(-1, &status, 0) != -1 || errno != ECHILD)
		continue ;
	if (WIFEXITED(status))
		g_last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_code = 128 + WTERMSIG(status);
	else
		g_last_exit_code = status;
	return (g_last_exit_code);
}

void	check_cmd_list(t_data *data)
{
	t_command *cmd;

	cmd = data->cmd;
	printf("\nExecution: Commands received:\n");
	while (cmd)
	{
		printf("\tCommand = %s\n", cmd->command);
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		for (int i = 0; cmd->args[i]; i++)	
			printf("\tArgs[%d] = %s\n", i, cmd->args[i]);
		printf("\tPipe_output = %d\n", cmd->pipe_output);
		if (cmd->io_fds && cmd->io_fds->infile)
			printf("\tInfile: %s\n", cmd->io_fds->infile);
		if (cmd->io_fds && cmd->io_fds->outfile)
			printf("\tOutfile: %s\n", cmd->io_fds->outfile);
		if (cmd->prev == NULL)
			printf("\tprev = NULL\n");
		else
			printf("\tprev = %s\n", cmd->prev->command);
		if (cmd->next == NULL)
			printf("\tnext = NULL\n");
		else
			printf("\tnext = %s\n", cmd->next->command);
		printf("\n");
		cmd = cmd->next;
	}
	printf("\n");
}

/* execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate. If the command is a builtin
*	and its output is not piped to another command, it is not forked.
*	Returns the exit code of the last child to terminate.
*/
int	execute(t_data *data)
{
	t_command	*cmd;
	int			pid;
	int			ret;

	ret = CMD_NOT_FOUND;
	cmd = data->cmd;
	if (!cmd || cmd->command == NULL)
		return (ret);
	check_cmd_list(data);
	if (!create_pipes(data) || !open_infile_outfile(cmd->io_fds))
		return (0);
	pid = -1;
	while (pid != 0 && cmd)
	{
		if (!cmd->pipe_output)
			ret = execute_builtin(data, cmd);
		if (ret != CMD_NOT_FOUND)
		{
			free_data(data, false);
			return (ret);
		}
		pid = fork();
		if (pid == -1)
			errmsg_cmd("fork", NULL, strerror(errno), errno);
		else if (pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}
