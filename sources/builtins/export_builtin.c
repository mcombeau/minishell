#include "minishell.h"

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
	if (!tmp[1])
		return (tmp);
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
*	Returns 0 if all args were successfully added to env,
*	or 1 if one or more args were not added to env.
*/
int	export_builtin(t_data *data, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if (ft_strchr(args[i], '=') != NULL)
		{
			if (!is_valid_env_var_key(args[i]))
			{
				errmsg_cmd("export", args[i], "not a valid identifier", false);
				ret = EXIT_FAILURE;
			}
			else
			{
				tmp = get_key_value_pair(args[i]);
				if (!tmp)
				{
					errmsg_cmd("export", NULL, "Could not get key value pair", 1);
					exit_shell(data, EXIT_FAILURE);
				}
				set_env_var(data, tmp[0], tmp[1]);
				free(tmp);
			}
		}
		i++;
	}
	return (ret);
}
