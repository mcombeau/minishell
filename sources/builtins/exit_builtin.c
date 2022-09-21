/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:32:33 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/21 15:19:25 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* get_exit_code:
*	Gets the exit code from the arguments given to the exit builtin.
*	Returns 0 if no arguments were provided.
*	Returns 2 in case argument is not digits.
*	Returns the numeric exit code on success.
*/
static int	get_exit_code(char **args)
{
	int	i;

	if (!args || !args[0] || !args[1])
		return (EXIT_SUCCESS);
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
	if (args[2])
	{
		errmsg_cmd("exit", NULL, "too many arguments", 1);
		return (EXIT_FAILURE);
	}
	return (ft_atoi(args[1]));
}

/* exit_should_execute:
*	Checks if the exit builtin should execute or not. Exit should only execute if
*	if is the first and only command in the command list. Example:
*		exit | ls
*		ls | exit
*		exit 0 | exit 1
*		ls | exit | wc -l
*	None of these examples should execute the exit builtin.
*	If there is no command list, this means exit builtin was called because of
*	ctrl+D input, in which case it should execute as if user had input "exit" alone.
*	Returns true if exit is OK to execute, false if not.
*/
static bool	exit_should_execute(t_data *data)
{
	t_command	*cmd;

	if (!data->cmd)
		return (true);
	cmd = data->cmd;
	while (cmd && ft_strcmp(cmd->command, "exit") != 0) 
		cmd = cmd->next;
	if (cmd->prev != NULL || cmd->next != NULL)
		return (false);
	return (true);
}

/* exit_builtin:
*	Executes the exit builtin.
*	If alone, prints exit and exits the shell with the provided exit code, or 0.
*	If piped, exits the child process with the provided exit code and does not exit
*	minishell.
*	In case of failure due to invalid arguments, does not exit the shell
*	and returns an error exit code (1 or 2) instead.
*/
int	exit_builtin(t_data *data, char **args)
{
	int	exit_code;

	exit_code = get_exit_code(args);
	if (data->cmd && data->cmd->io_fds)
		restore_io(data->cmd->io_fds);
	if (!exit_should_execute(data) || exit_code == EXIT_FAILURE)
		return (exit_code);
	printf("exit\n");
	exit_shell(data, exit_code);
	return (2);
}
