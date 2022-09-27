/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:28:59 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/27 14:18:57 by mcombeau         ###   ########.fr       */
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

/* check_command_not_found:
*	Searches for the reason a command was not found in the system binaries.
*	Returns an error message and status if the command is invalid,
*	returns EXIT_SUCCESS if the command is valid and should be executed
*	as a local executable.
*/
static int	check_command_not_found(t_data *data, t_command *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		if (get_env_var_index(data->env, "PATH") == -1)
			return (errmsg_cmd(cmd->command, NULL,
					"No such file or directory", CMD_NOT_FOUND));
		return (errmsg_cmd(cmd->command, NULL,
				"command not found", CMD_NOT_FOUND));
	}
	if (!is_valid_cmd(cmd->command))
		return (errmsg_cmd(cmd->command, NULL,
				"command not found", CMD_NOT_FOUND));
	if (cmd_is_dir(cmd->command))
		return (errmsg_cmd(cmd->command, NULL,
				"Is a directory", CMD_NOT_EXECUTABLE));
	if (access(cmd->command, F_OK) != 0)
		return (errmsg_cmd(cmd->command, NULL, strerror(errno), CMD_NOT_FOUND));
	else
	{
		if (access(cmd->command, F_OK | X_OK) != 0)
			return (errmsg_cmd(cmd->command, NULL,
					strerror(errno), CMD_NOT_EXECUTABLE));
	}
	return (EXIT_SUCCESS);
}