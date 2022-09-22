/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:08:47 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/22 14:51:57 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Add ability to use -c option to give line to parse without readline
// for automated testing.
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
			g_last_exit_code = execute(&data);
		else
			g_last_exit_code = 2;
		free_data(&data, false);
	}
	exit_shell(&data, g_last_exit_code);
	return (0);
}
