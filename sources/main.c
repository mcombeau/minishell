#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data data;

	if (!init_env(env))
	{
		errmsg("Fatal", NULL, "Could not initialize environment", 1);
		exit_shell(EXIT_FAILURE);
	}
	if (ac >= 2 && (av[1][0] == 't' || av[1][0] == 'T'))
	{
		test_minishell(ac, av);
		exit_shell(EXIT_SUCCESS);
	}
	init_data(&data, env);
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		data.user_input = readline(PROMPT);
		if (data.user_input == NULL)
			exit_builtin(NULL);
		printf("input = %s\n", data.user_input);
		add_history(data.user_input);
		if (tokenization(&data, data.user_input) == 1)
			printf("Error with tokenization\n");
		define_token(&data.token);
		check_consecutives(&data.token);
		free(data.user_input);
	}
	exit_shell(EXIT_SUCCESS);
	return (0);
}
