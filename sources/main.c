#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;

	(void)ac;
	(void)av;
	if (!init_env(env))
		// print error message here.
		exit_shell(); // exit with error code.
//	test_execution();
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		str = readline(PROMPT);
		if (str == NULL)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit_shell();
		}
		printf("str = %s\n", str);
		add_history(str);
		free(str);
	}
	exit_shell();
	return (0);
}
