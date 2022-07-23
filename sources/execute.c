#include "minishell.h"

/* execute_builtin:
*	Executes the given command if it is a builtin command.
*	Returns -1 if the command is not a builtin command.
*	Returns 0 or 1 if the builtin command succeeded or failed.
*/
static int	execute_builtin(t_command *cmd)
{
	int	ret;

	ret = -42;
	if (ft_strncmp(cmd->command, "cd", 3))
		ret = cd_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5))
		ret = echo_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4))
		ret = env_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5))
		ret = exit_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7))
		ret = export_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4))
		ret = pwd_builtin(cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6))
		ret = unset_builtin(cmd->args);
	return (ret);
}

/* execute_sys_bin:
*	Executes the command's system binary file if it can be found
*	among the environment executable paths.
*	Returns -42 if a path to the executable bin file cannot be
*	found. Returns 1 in case of failure to run existing, executable
*	file.
*/
static int	execute_sys_bin(t_command *cmd)
{
	cmd->path = get_cmd_path(cmd->command);
	if (!cmd->path)
		return (-42);
	if (execve(cmd->path, cmd->args, g_env_vars) == -1)
		errmsg("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/* execute_local_bin:
*	Attempts to execute the given command as is, in case
*	it is a local directory file or already contains the
*	path to bin.
*	Returns -42 if the command is not an existing executable
*	file. Returns 1 in case of failure to launch executable.
*/
static int	execute_local_bin(t_command *cmd)
{
	if (access(cmd->command, F_OK | X_OK) != 0)
		return (-42);
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
static int	execute_command(t_command *cmds, t_command *cmd_to_exec)
{
	int	ret;

	if (!cmd_to_exec->command)
		exit(errmsg("child process", NULL, "parsing error: no command to execute!", EXIT_FAILURE));
	set_pipe_fds(cmds, cmd_to_exec);
	// TODO: Deal with in/out file.
	ret = execute_builtin(cmd_to_exec);
	if (ret != -42)
		exit(ret);
	ret = execute_sys_bin(cmd_to_exec);
	if (ret != -42)
		exit(ret);
	ret = execute_local_bin(cmd_to_exec);
	if (ret != -42)
		exit(ret);
	exit(errmsg(cmd_to_exec->command, NULL, "command not found", EXIT_FAILURE));
}

/* create_children:
*	Creates a child process for each command in the pipeline.
*/
static void	create_children(t_command *cmd)
{
	t_command	*tmp;
	int			pid;

	tmp = cmd;
	pid = -1;
	while (pid != 0 && tmp)
	{
		pid = fork();
		if (pid == -1)
			errmsg("fork", NULL, strerror(errno), errno);
		else if (pid == 0)
			execute_command(cmd, tmp);
		tmp = tmp->next;
	}
}

/* execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate.
*	Returns the exit code of the last child to terminate.
*/
int	execute(t_command *cmds)
{
	int	status;

	create_children(cmds);
	close_pipe_fds(cmds, NULL);
	while (waitpid(-1, &status, 0) != -1 || errno != ECHILD)
		continue ;
	return (0); // TODO: Return with last child's exit code or something
}
