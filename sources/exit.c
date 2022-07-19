#include "minishell.h"

/* free_env_vars:
*	Frees the global variable g_env_vars.
*/
static void	free_env_vars(void)
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

/* exit_shell:
*	Cleanly exits the minishell program. 
*/
void	exit_shell(void)
{
	free_env_vars();
	exit(0);
}
