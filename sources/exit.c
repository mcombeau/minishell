#include "minishell.h"

/* exit_shell:
*	Cleanly exits the minishell program. 
*/
void	exit_shell(t_command *cmd_list, int	exno)
{
	if (cmd_list)
		free_cmd_list(cmd_list);
	free_env_vars();
	exit(exno);
}
