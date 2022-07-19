#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	test_env(ac, av, env);
	exit_shell();
	return (0);
}
