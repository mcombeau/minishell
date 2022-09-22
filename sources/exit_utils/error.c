/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:06:15 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/22 16:43:44 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* errmsg_cmd:
*	Prints an error message to the standard error, prefixed with the
*	program name.
*	Returns with the specified error number.
*/
int	errmsg_cmd(char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = false;
	if (command == NULL)
		msg = ft_strdup("minishell");
	else
		msg = ft_strjoin("minishell: ", command);
	msg = ft_strjoin(msg, ": ");
	if (detail != NULL)
	{
		if (ft_strncmp(command, "export", 7) == 0
			|| ft_strncmp(command, "unset", 6) == 0)
			detail_quotes = true;
		if (detail_quotes)
			msg = ft_strjoin(msg, "`");
		msg = ft_strjoin(msg, detail);
		if (detail_quotes)
			msg = ft_strjoin(msg, "`");
		msg = ft_strjoin(msg, ": ");
	}
	msg = ft_strjoin(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (error_nb);
}

void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strjoin("minishell: ", errmsg);
	if (quotes)
		msg = ft_strjoin(msg, "`");
	else
		msg = ft_strjoin(msg, ": ");
	msg = ft_strjoin(msg, detail);
	if (quotes)
		msg = ft_strjoin(msg, "`");
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
}

bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}