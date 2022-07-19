#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *str;

	if (!init_env(env))
		// print error message here.
		exit_shell(); // exit with error code.
	while (1)
	{
		str = readline("\033[0;35m➜\033[0;m \033[0;33mMinishell >\033[0;m");
		printf("str = %s\n", str);
		add_history(str);
		free(str);
	}
	exit_shell();
	return (0);
}
