#include "minishell.h"

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

void	free_cmd_list(t_command *cmd_list)
{
	t_command	*tmp;

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