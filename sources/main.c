/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:08:47 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/24 15:18:44 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Add ability to use -c option to give line to parse without readline
// for automated testing.
static bool	start_check(t_data *data, int ac, char **av)
{
	if (ac != 1 && ac != 3)
		return (usage_message(false));
	if (ac == 3)
	{
		data->interactive = false;
		if (!av[1] || (av[1] && ft_strcmp(av[1], "-c") != 0))
			return (usage_message(false));
		else if (!av[2] || (av[2] && av[2][0] == '\0'))
			return (usage_message(false));
	}
	else
		data->interactive = true;
	return (true);
}

static bool	parse_user_input(t_data *data)
{
	if (data->user_input == NULL)
		exit_builtin(data, NULL, true);
	else if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	add_history(data->user_input);
	if (tokenization(data, data->user_input) == FAILURE)
		return (false);
	if (data->token->type == END)
		exit_shell(data, g_last_exit_code);
	if (check_if_var(&data->token) == FAILURE)
		return (false);
	var_expander(data, &data->token);
	handle_quotes(data);
	var_tokenization(data);
	create_commands(data, data->token);
	print_cmd_list(data);
	return (true);
}

void	minishell_interactive(t_data *data)
{
	while (1)
	{
		ignore_sigquit();
		set_interactive_signal_trap();
		data->user_input = readline(PROMPT);
		set_noninteractive_signal_trap();
		if (parse_user_input(data) == true)
			g_last_exit_code = execute(data);
		else
			g_last_exit_code = 2;
		free_data(data, false);
	}
}

void	minishell_noninteractive(t_data *data, char *arg)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(arg, ';');
	if (!user_inputs)
		exit_shell(data, EXIT_FAILURE);
	i = 0;
	while (user_inputs[i])
	{
		data->user_input = ft_strdup(user_inputs[i]);
		if (parse_user_input(data) == true)
			g_last_exit_code = execute(data);
		else
			g_last_exit_code = 2;
		i++;
		free_data(data, false);
	}
	free_tab(user_inputs);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(&data, ac, av) || !init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	if (data.interactive)
		minishell_interactive(&data);
	else
		minishell_noninteractive(&data, av[2]);
	exit_shell(&data, g_last_exit_code);
	return (0);
}
