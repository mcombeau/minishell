/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:08:47 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/18 15:13:33 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	start_check(int ac, char **av)
{
	if (ac != 1 || !av)
	{
		errmsg_cmd("Usage", NULL, "./minishell", 1);
		return (false);
	}
	return (true);
}

static bool	parse_user_input(t_data *data)
{
	if (data->user_input == NULL)
		exit_builtin(data, NULL);
	else if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	printf("\n\e[92m------- MAIN: Parse user input.\n");
	add_history(data->user_input);
	if (tokenization(data, data->user_input) == FAILURE)
		return (false);
	if (data->token->type == END)
		exit_shell(data, EXIT_SUCCESS);
	if (check_if_var(&data->token) == FAILURE)
		return (false);
	var_expander(data, &data->token);
	handle_quotes(data);
	var_tokenization(data);
	printf("\n\e[32m------- MAIN: Create commands.\n");
	create_commands(data, data->token);
	print_cmd_list(data);
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(ac, av) || !init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	while (1)
	{
		ignore_sigquit();
		set_interactive_signal_trap();
		data.user_input = readline(PROMPT);
		set_noninteractive_signal_trap();
		if (parse_user_input(&data) == true)
		{
			printf("\n\e[36m------- MAIN: Launch exec.\e[0m\n");
			execute(&data);
			printf("\e[36m------- Exec done.\e[0m\n");
		}
		free_data(&data, false);
	}
	exit_shell(&data, EXIT_SUCCESS);
	return (0);
}
