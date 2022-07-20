#include "minishell.h"

/* env_var_count:
*	Counts how many original environment variables there are.
*	Returns the number of environment variables.
*/
int	env_var_count(char **env)
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
*	Returns the index of the variable in the environment
*	matching the given string. Partial variable names are not
*	supported: the given string must be a full variable name.
*	Returns -1 if the string cannot be found in the environment.
*/
int	get_env_var_index(char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (g_env_vars[i])
	{
		if (ft_strncmp(tmp, g_env_vars[i], ft_strlen(tmp)) == 0)
			return (i);
		i++;
	}
	return (-1);
}