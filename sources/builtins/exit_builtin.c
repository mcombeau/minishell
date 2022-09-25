/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:32:33 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/25 15:27:11 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

/* get_exit_code:
*	Gets the exit code from the arguments given to the exit builtin.
*	Returns 0 if no arguments were provided.
*	Returns 2 in case argument is not digits.
*	Returns the numeric exit code on success.
*/
static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_last_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
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
static bool	exit_should_execute(t_data *data, char **args)
{
	t_command	*cmd;

	if (!args || !data->cmd)
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
int	exit_builtin(t_data *data, char **args, bool direct_call)
{
	int		exit_code;
	bool	error;

	error = false;
	if (!args || direct_call)
		exit_code = g_last_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			return (errmsg_cmd("exit", args[1],
					"numeric argument required", 2));
		else if (args[2])
			return (errmsg_cmd("exit", NULL, "too many arguments", 1));
		if (data->cmd && data->cmd->io_fds)
			restore_io(data->cmd->io_fds);
		if (!exit_should_execute(data, args) || exit_code == EXIT_FAILURE)
			return (exit_code);
	}
	if (data->interactive)
		printf("exit\n");
	exit_shell(data, exit_code);
	return (2);
}
