#include "minishell.h"

/* realloc_env_vars:
*	Reallocates memory for the global variable g_env_vars.
*
*	Returns a pointer to the new environment variables
*	or NULL in case of a memory allocation error.
*/
static char	**realloc_env_vars(int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (g_env_vars[i] && i < size)
	{
		new_env[i] = ft_strdup(g_env_vars[i]);
		free(g_env_vars[i]);
		i++;
	}
	free(g_env_vars);
	return (new_env);
}

/* set_env_var:
*	Adds an environment variable with the given key
*	corresponding to the given value. If the key already
*	exists in the environment variables, the value will
*	be overwritten. If not, it creates a new entry.
*
*	Returns 1 if the operation was successful, or 0 if
*	in case of error.
*/
bool	set_env_var(char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	printf("\e[35mSet env var: key = %s, value = %s\n\e[0m", key, value);
	if (idx != -1 && g_env_vars[idx])
	{
		free(g_env_vars[idx]);
		g_env_vars[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = env_var_count(g_env_vars);
		g_env_vars = realloc_env_vars(idx + 1);
		if (!g_env_vars)
			return (false);
		g_env_vars[idx] = ft_strjoin(key, tmp);
	}
	free(tmp);
	return (true);
}

/* remove_env_var:
*	Removes the variable at the given index from the
*	environment variables.
*
*	Returns 1 if the removal was successful, 0 if case
*	of an invalid index or a memory allocation error.
*/
bool	remove_env_var(int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(g_env_vars))
		return (false);
	free(g_env_vars[idx]);
	i = idx;
	count = idx;
	while (g_env_vars[i + 1])
	{
		g_env_vars[i] = ft_strdup(g_env_vars[i + 1]);
		free(g_env_vars[i + 1]);
		count++;
		i++;
	}
	g_env_vars = realloc_env_vars(count);
	if (!g_env_vars)
		return (false);
	return (true);
}