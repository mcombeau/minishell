#include "minishell.h"

/* env_builtin:
*	Executes the builtin env command: Prints the environment variables.
*/
int	env_builtin(char **args)
{
	int	i;

	(void)args;
	i = 0;
	if (!g_env_vars)
		return (EXIT_FAILURE);
	while (g_env_vars[i])
		ft_putendl_fd(g_env_vars[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
