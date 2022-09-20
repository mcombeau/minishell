/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:28:59 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/20 17:29:04 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_cmd(char *cmd)
{
	if (!cmd || cmd[0] == '\0' || !ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (false);
	return (true);
}

bool	cmd_is_dir(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
