#include "minishell.h"

/* env_builtin:
*	Executes the builtin env command: Prints the environment variables.
*/
void	env_builtin(void)
{
	int	i;

	i = 0;
	while (g_env_vars[i])
		ft_putendl_fd(g_env_vars[i++], STDOUT_FILENO);
}
