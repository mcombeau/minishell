#include "minishell.h"

/* env_var_count:
*	Counts how many original environment variables there are.
*	Returns the number of environment variables.
*/
static int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/* init_env:
*	Initializes a global variable, g_env_vars, with the contents
*	of the environment variables inherited from the original shell.
*	Returns 0 on failure, 1 on success.
*/
bool	init_env(char **env)
{
	int	i;

	g_env_vars = ft_calloc(env_var_count(env) + 1, sizeof * g_env_vars);
	i = 0;
	while (env[i])
	{
		g_env_vars[i] = ft_strdup(env[i]);
		if (!g_env_vars[i])
			return (false);
		i++;
	}
	return (true);
}

/* sh_builtin_env:
*	Executes the builtin env command: Prints the environment variables.
*/
void	sh_builtin_env(void)
{
	int	i;

	i = 0;
	while (g_env_vars[i])
		ft_putendl_fd(g_env_vars[i++], STDOUT_FILENO);
}

