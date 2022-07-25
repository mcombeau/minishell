#include "minishell.h"

/* exit_shell:
*	Cleanly exits the minishell program by closing all opened
*	fds and freeing all allocated memory.
*/
void	exit_shell(t_command *cmd_list, int	exno)
{
	if (cmd_list && cmd_list->io_fds)
		close_fds(cmd_list, true);
	if (cmd_list)
		free_cmd_list(cmd_list);
	free_env_vars();
	exit(exno);
}
