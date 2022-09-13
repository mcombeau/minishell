#include "minishell.h"

static bool	start_check(int ac, char **av, char **env)
{
	if (ac != 1 || !av)
	{
		errmsg_cmd("Usage", NULL, "./minishell", 1);
		return (false);
	}
	if (!init_env(env))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	/*	if (ac >= 2 && (av[1][0] == 't' || av[1][0] == 'T'))
	{
		test_minishell(ac, av);
		exit_shell(NULL, EXIT_SUCCESS);
	}*/
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_data data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(ac, av, env))
		exit_shell(NULL, EXIT_FAILURE);
	init_data(&data, env);
	while (1)
	{
		ignore_sigquit();
		set_signal_trap();
		data.user_input = readline(PROMPT);
		if (data.user_input == NULL)
			exit_builtin(&data, NULL);
		else if (ft_strcmp(data.user_input, "\0") == 0)
			continue;
		printf("\n\e[92m------- MAIN: Parse user input.\n");
		printf("input = \"%s\"\n", data.user_input);
		add_history(data.user_input);
		if (tokenization(&data, data.user_input) == FAILURE)
		{
			free_data(&data, false);
			continue;
		}
		if (data.token->type == END)
			break;
		if (check_if_var(&data.token) == FAILURE)
		{
			free_data(&data, false);
			continue;
		}
		var_expander(&data, &data.token);
		handle_quotes(&data);
		var_tokenization(&data);
		print_token(data.token);
		printf("\n\e[32m------- MAIN: Create commands.\n");
		create_commands(&data, data.token);
		printf("\n\e[36m------- MAIN: Launch exec.\e[0m\n");
		execute(&data);
		printf("\e[36m------- Exec done.\e[0m\n");
	}
	exit_shell(&data, EXIT_SUCCESS);
	return (0);
}
