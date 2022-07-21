#include "minishell.h"

/* unset_builtin:
*	Removes the environment variables with the given keys
*	after checking if they are valid keys.
*	Does nothing if the key is not in the environment.
*	Returns true always.
*/
bool	unset_builtin(char **args)
{
	int	i;
	int	idx;

	i = 0;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
			printf("minishell: unset: `%s`: not a valid identifier\n", args[i]);
		else
		{
			idx = get_env_var_index(args[i]);
			if (idx != - 1)
				remove_env_var(idx);
		}
		i++;
	}
	return (true);
}