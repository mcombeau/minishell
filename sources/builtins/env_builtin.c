#include "minishell.h"

/* env_builtin:
*	Executes the builtin env command: Prints the environment variables.
*/
bool	env_builtin(void)
{
	int	i;

	i = 0;
	while (g_env_vars[i])
		ft_putendl_fd(g_env_vars[i++], STDOUT_FILENO);
	return (true);
}
