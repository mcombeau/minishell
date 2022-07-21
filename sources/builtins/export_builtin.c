#include "minishell.h"

static bool	is_valid_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

static char	**get_key_value(char *arg)
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
		i++;
	}
	return (tmp);
}

bool	export_builtin(char **args)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!args[i])
		return (env_builtin());
	while (args[i])
	{
		if (ft_strchr(args[i], '=') != NULL
			&& is_valid_var_key(args[i]))
		{
			tmp = get_key_value(args[i]);
			set_env_var(tmp[0], tmp[1]);
			free(tmp);
		}
		i++;
	}
	return (true);
}
