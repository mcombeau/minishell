#include "minishell.h"

/* close_fds:
*	Closes opened file descriptors, including pipes and input and
*	output fds. If close_backups is set to true, it also closes
*	backup STDIN and STDOUT file descriptors.
*/
void	close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		close(cmds->io_fds->fd_in);
		close(cmds->io_fds->fd_out);
		if (close_backups)
		{
			restore_io(cmds->io_fds);
			close(cmds->io_fds->stdin_backup);
			close(cmds->io_fds->stdout_backup);
		}
	}
	close_pipe_fds(cmds, NULL);
}

/* free_strs_array:
*	Frees an array of strings.
*/
void	free_str_array(char **strs)
{
	int i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}

/* free_env_vars:
*	Frees the global variable g_env_vars.
*/
void	free_env_vars(void)
{
	int	i;

	if (g_env_vars == NULL)
		return ;
	i = 0;
	while (g_env_vars[i])
	{
		free(g_env_vars[i]);
		i++;
	}
	free(g_env_vars);
}

/* free_io:
*	Frees the input/output fd structure.
*/
void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->infile)
		free(io->infile);
	if (io->outfile)
		free(io->outfile);
	if (io)
		free(io);
}

/* free_cmd_list:
*	Frees the list of commands.
*/
void	free_cmd_list(t_command *cmd_list)
{
	t_command	*tmp;

	printf("\n\tFreeing execute command list.\n");
	tmp = cmd_list;
	if (tmp->io_fds)
		free_io(tmp->io_fds);
	while (tmp)
	{
		if (tmp->args)
			free_str_array(tmp->args);
		tmp = tmp->next;
	}
	if (tmp)
		free(tmp);
}
