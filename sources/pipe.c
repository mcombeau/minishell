#include "minishell.h"

/* close_pipe_fds:
*	Closes the pipe fds of all commands. A pointer to a command to skip
*	can be specified to skip closing that command's pipe fds:
*		- The parent will specify NULL for the skip command while closing
*		all pipe fds.
*		- The child will specify its own command as skip command while
*		closing all pipe fds so as to not accidentally close its own
*		pipe fds.
*/
void	close_pipe_fds(t_command *cmds, t_command *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			errmsg(cmds->command, NULL, "Closing pipe fds", 0);
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool	create_pipes(t_command *cmd_list)
{
	int			*fd;
	t_command	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->pipe || (tmp->prev && tmp->prev->pipe))
		{
			printf("Creating pipes for cmd [%s]\n", tmp->command);
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				//TODO: free cmd list
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

/* set_pipe_fds:
*	Sets the pipe fds for this command. If the previous command
*	was piped to this one, sets the input as the read end of
*	the previous command. If this command is piped to the
*	next, sets the output ad the write end of the pipe.
*		pipe_fd[0] = read end of pipe.
*		pipe_fd[1] = write end of pipe.
*	Returns true when the pipe file descriptors are set.
*/
bool	set_pipe_fds(t_command *cmds, t_command *curr_cmd)
{
	if (!curr_cmd)
		return (false);
	if (curr_cmd->prev && curr_cmd->prev->pipe)
		dup2(curr_cmd->pipe_fd[0], STDIN_FILENO);
	if (curr_cmd->pipe)
		dup2(curr_cmd->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, curr_cmd);
	return (true);
}