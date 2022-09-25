/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:03:08 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/25 18:48:02 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* change_dir:
*	Changes the current working directory and updates the
*	OLDPWD environment variable.
*	Returns 1 on success, 0 on failure.
*/
static bool	change_dir(t_data *data, char *path)
{
	char	*cwd;
	char	buff[BUFSIZ];

	cwd = getcwd(buff, BUFSIZ);
	if (chdir(path) == EXIT_SUCCESS)
	{
		set_env_var(data, "OLDPWD", cwd);
		set_env_var(data, "PWD", getcwd(buff, BUFSIZ));
	}
	else
	{
		errmsg_cmd("cd", path, strerror(errno), errno);
		return (false);
	}
	return (true);
}

/* cd_builtin:
*	Executes the builtin cd command by changing the working directory.
*	Returns 0 on success, 1 on failure.
*/
int	cd_builtin(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) 
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var_value(data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		printf("%s\n", get_env_var_value(data->env, "OLDPWD"));
		return (!change_dir(data, get_env_var_value(data->env, "OLDPWD")));
	}
	return (!change_dir(data, args[1]));
}
