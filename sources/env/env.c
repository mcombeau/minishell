#include "minishell.h"

char	**g_env_vars;

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

	if (!env || !env[0])
		errmsg("Warning", NULL,
			"No environment. Please provide paths for commands.", 1);
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
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}

/* get_env_var_value:
*	Searches for the given variable in the environment variables.
*
*	Returns a pointer to the value of the variable in the environment
*	matching the given string. Partial variable names are not
*	supported: the given string must be a full variable name.
*	Returns NULL if the string cannot be found in the environment.
*/
char *get_env_var_value(char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (g_env_vars[i])
	{
		if (ft_strncmp(tmp, g_env_vars[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (ft_strchr(g_env_vars[i], '=') + 1);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

/* is_valid_env_var_key:
*	Checks if the key is a valid name for an evironment
*	variable.
*	Returns true if the key contains only alphanumeric chars
*	or '_', or false if not.
*/
bool	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
