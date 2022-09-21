/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:28:59 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/21 14:39:13 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* is_valid_cmd:
*	Checks if the given command is a valid command. An empty string, a [.] or a
*	[..] are not valid commands.
*	Returns true if the command is valid, false if not.
*/
bool	is_valid_cmd(char *cmd)
{
	if (!cmd || cmd[0] == '\0' || !ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (false);
	return (true);
}

/* cmd_is_dir:
*	Checks if the command is a directory rather than an executable.
*	Returns true if the command is a directory, false if not.
*/
bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}
