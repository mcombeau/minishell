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

/* get_env_var_index:
*	Searches for the given variable in the environment variables.
*
*	Returns the index of the first variable in the environment
*	matching the given string.
*	Returns -1 if the string cannot be found in the environment.
*/
int	get_env_var_index(char *var)
{
	int		i;

	i = 0;
	while (g_env_vars[i])
	{
		if (ft_strncmp(var, g_env_vars[i], ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

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
