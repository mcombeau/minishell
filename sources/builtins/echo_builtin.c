#include "minishell.h"

/* echo_print:
*	Prints a string for the echo builtin, while removing quote
*	characters and adding spaces between words.
*/
/*
static void	echo_print(char *arg)
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
*/
/* echo_builtin:
*	Executes the echo builtin command: prints the given strings
*	and adds a \n character or not depending on the -n option.
*	Returns 1 on completion.
*/
int	echo_builtin(char **args)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	if (!args[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(args[1], "-n", 3) == 0)
		n_flag = true;
	i = 1;
	if (n_flag)
		i++;
	while (args[i])
	{
//		echo_print(args[i]);
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}