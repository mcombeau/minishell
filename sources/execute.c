#include "minishell.h"

/* execute_builtin:
*	Executes the given command if it is a builtin command.
*	Returns -1 if the command is not a builtin command.
*	Returns 0 or 1 if the builtin command failed or succeeded.
*/
static int	execute_builtin(t_command *cmd)
{
	int	ret;

	ret = -1;
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

static int	execute_command(t_command *cmds, t_command *cmd_to_exec)
{
	int	ret;

	ret = EXIT_SUCCESS;
	set_pipe_fds(cmds, cmd_to_exec);
	// TODO: Deal with in/out file.
	if (execute_builtin(cmd_to_exec) != -1)
		return (ret);
	// TODO: If not builtin, try to find binary path
	// TODO: If not binary, try to find exec in cwd
	// TODO: Display error msg if none of the above worked
	// TODO: Exit child process.
	return (ret);
}

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


int	execute(t_command *cmds)
{
	int	status;

	create_children(cmds);
	close_pipe_fds(cmds, NULL);
	while (waitpid(-1, &status, 0) != -1 || errno != ECHILD)
		continue ;
	return (0); // TODO: Return with last child's exit code or something
}
