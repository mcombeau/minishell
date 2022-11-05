/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:32:33 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/05 12:17:05 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check_out_of_range:
*	Checks if the number goes over LONG_MAX or LONG_MIN.
*	Sets an error boolean to true if the number is out of range, false if not.
*/
static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

/* ft_atoi_long:
*	Transforms a string comprised of digits into a long integer.
*	Returns the long integer. In case of error, sets an error boolean
*	to true.
*/
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
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

/* is_quiet_mode:
*	If exit is not called alone, it should not print "exit".
*	Returns true if exit should not be printed. False if exit was called
*	alone and the "exit" message should be printed.
*/
static bool	is_quiet_mode(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
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
	int		exit_code;
	bool	error;
	bool	quiet;

	quiet = is_quiet_mode(data);
	error = false;
	if (!quiet && data->interactive)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_code = g_last_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			exit_code = errmsg_cmd("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (errmsg_cmd("exit", NULL, "too many arguments", 1));
	}
	exit_shell(data, exit_code);
	return (2);
}
