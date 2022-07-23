#include "minishell.h"

/* unset_builtin:
*	Removes the environment variables with the given keys
*	after checking if they are valid keys.
*	Does nothing if the key is not in the environment.
*	Returns 0 if all args were successfully unset, or 1 if
*	one or more args could not be unset.
*/
int	unset_builtin(char **args)
{
	int	i;
	int	idx;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 0;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg("unset", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else
		{
			idx = get_env_var_index(args[i]);
			if (idx != - 1)
				remove_env_var(idx);
		}
		i++;
	}
	return (ret);
}