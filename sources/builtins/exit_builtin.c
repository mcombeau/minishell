#include "minishell.h"

/* exit_builtin:
*	Executes the exit builtin. Prints exit and exits the shell with
*	the provided exit code, or 0.
*	In case of failure due to too many args, does not exit the shell
*	and returns 1 instead.
*/
int	exit_builtin(char **args)
{
	int	i;
	printf("exit\n");
	if (!args || !args[1])
		exit_shell(EXIT_SUCCESS);
	if (args[1])
	{
		i = 0;
		while (args[1][i])
		{
			if (!isdigit(args[1][i]))
				exit_shell(errmsg("exit", args[1], "numeric argument required", 2));
			i++;
		}
	}
	if (args[2])
	{
		errmsg("exit", NULL, "too many arguments", 1);
		return (EXIT_FAILURE);
	}
	else
		exit_shell(ft_atoi(args[1]));
	return (EXIT_SUCCESS);
}
