/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:32:33 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/19 17:09:40 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_code(char **args)
{
	int	i;

	if (!args || !args[1])
		return (EXIT_SUCCESS);
	if (args[1])
	{
		i = 0;
		if (args[1][i] == '-' || args[1][i] == '+')
			i++;
		while (args[1][i])
		{
			if (!isdigit(args[1][i]))
				return (errmsg_cmd("exit", args[1],
						"numeric argument required", 2));
			i++;
		}
	}
	return (ft_atoi(args[1]));
}

/* exit_builtin:
*	Executes the exit builtin. Prints exit and exits the shell with
*	the provided exit code, or 0.
*	In case of failure due to too many args, does not exit the shell
*	and returns 1 instead.
*/
int	exit_builtin(t_data *data, char **args)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (data->cmd && (ft_strcmp(data->cmd->command, "exit") != 0))
		return (exit_code);
	else if (data->cmd && data->cmd->io_fds)
		restore_io(data->cmd->io_fds);
	printf("exit\n");
	exit_code = get_exit_code(args);
	if (args && args[2])
	{
		errmsg_cmd("exit", NULL, "too many arguments", 1);
		return (EXIT_FAILURE);
	}
	exit_shell(data, exit_code);
	return (2);
}
