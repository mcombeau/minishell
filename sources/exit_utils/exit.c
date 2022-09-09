#include "minishell.h"

/* exit_shell:
*	Cleanly exits the minishell program by closing all opened
*	fds and freeing all allocated memory.
*/
void	exit_shell(t_data *data, int exno)
{
	if (data->cmd && data->cmd->io_fds)
		close_fds(data->cmd, true);
//	if (data->cmd)
//		free_cmd_list(data->cmd);
	free_data(data, true);
	free_env_vars();
	exit(exno);
}
