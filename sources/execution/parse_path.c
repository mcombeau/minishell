/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:46:45 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/04 13:06:33 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* find_valid_cmd_path:
*	Checks access and permissions for each possible command path to find
*	a valid path to binay files for a command.
*	Returns the valid path to a command binary, or NULL if no valid path is
*	found.
*/
static char	*find_valid_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			errmsg_cmd("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_ptr(cmd_path);
		i++;
	}
	return (NULL);
}

/* get_paths_from_env:
*	Attempts to extract paths from the PATH environment variable.
*	Returns an array of paths on success. On failure, returns NULL.
*/
static char	**get_paths_from_env(t_data *data)
{
	char	**env_paths;

	if (get_env_var_index(data->env, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(get_env_var_value(data->env, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

/* get_cmd_path:
*	Searches the PATH environment variable for the location of the given
*	command's binary file.
*	Returns the path to the command binary file. NULL if no valid path
*	is found.
*/
char	*get_cmd_path(t_data *data, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = get_paths_from_env(data);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_str_tab(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(cmd, env_paths);
	if (!cmd_path)
	{
		free_ptr(cmd);
		free_str_tab(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
