#include "minishell.h"

void	echo_print(char *arg)
{
	char	**tmp;
	char	*str;
	int		i;

	tmp = ft_split(arg, ' ');
	i = 0;
	while (tmp[i])
	{
		str = ft_strtrim(tmp[i], "\"\'");
		ft_putstr_fd(str, STDOUT_FILENO);
		free(str);
		if (tmp[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

bool	sh_builtin_echo(char **args)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	if (!args[0])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return(true);
	}
	else if (ft_strncmp(args[0], "-n", 3) == 0)
		n_flag = true;
	i = 0;
	if (n_flag)
		i++;
	while (args[i])
	{
		echo_print(args[i]);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (true);
}