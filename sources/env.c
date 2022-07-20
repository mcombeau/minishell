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

static char	**realloc_env_vars(int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (false);
	i = 0;
	while (g_env_vars[i] && i < size)
	{
		new_env[i] = ft_strdup(g_env_vars[i]);
		free(g_env_vars[i]);
		i++;
	}
	free(g_env_vars);
	return(new_env);
}

bool	set_env_var(char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (idx != -1 && g_env_vars[idx])
	{
		free(g_env_vars[idx]);
		g_env_vars[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = env_var_count(g_env_vars);
		g_env_vars = realloc_env_vars(idx + 1);
		g_env_vars[idx] = ft_strjoin(key, tmp);
	}
	free(tmp);
	return (true);
}