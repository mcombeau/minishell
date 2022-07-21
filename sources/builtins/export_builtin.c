#include "minishell.h"

/* is_valid_var_key:
*	Checks if the key is a valid name for an evironment
*	variable.
*	Returns true if the key contains only alphanumeric chars
*	or '_', or false if not.
*/
static bool	is_valid_var_key(char *var)
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

/* get_key_value_pair:
*	Separates the given argument into a key-value pair
*	for the environment variable.
*	Returns an array of 2 strings containing the key and the
*	value of the new environment variable.
*	Returns NULL in case of error.
*/
static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	int		i;

	tmp = ft_split(arg, '=');
	if (!tmp)
		return (NULL);
	i = 2;
	while (tmp[i])
	{
		tmp[1] = ft_strjoin(tmp[1], "=");
		tmp[1] = ft_strjoin(tmp[1], tmp[i]);
		free(tmp[i]);
		i++;
	}
	return (tmp);
}

/* export_builtin:
*	Adds the given variables to the environment variables.
*	Returns true always.
*/
bool	export_builtin(char **args)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!args[i])
		return (env_builtin());
	while (args[i])
	{
		if (ft_strchr(args[i], '=') != NULL)
		{
			if (!is_valid_var_key(args[i]))
				printf("minishell: export: `%s`: not a valid identifier\n", args[i]);
			else
			{
				tmp = get_key_value_pair(args[i]);
				set_env_var(tmp[0], tmp[1]);
				free(tmp);
			}
		}
		i++;
	}
	return (true);
}
