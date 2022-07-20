#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr_fd("\033[0;35m➜\033[0;m \033[0;33mMinishell >\033[0;m",
					STDOUT_FILENO);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	(void)ac;
	(void)av;
	if (!init_env(env))
		// print error message here.
		exit_shell(); // exit with error code.
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		str = readline("\033[0;35m➜\033[0;m \033[0;33mMinishell >\033[0;m");
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
