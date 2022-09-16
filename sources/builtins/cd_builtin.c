#include "minishell.h"

/* change_dir:
*	Changes the current working directory and updates the
*	OLDPWD environment variable.
*	Returns 1 on success, 0 on failure.
*/
static bool	change_dir(t_data *data, char	*path)
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
	char	*home_path;

	home_path = get_env_var_value(data->env, "HOME");
	if (!args || !args[1] || ft_strncmp(args[1], "--", 3) == 0)
	{
		if (!home_path)
			return (errmsg_cmd("cd", NULL, "HOME not set", 0));
		return (!change_dir(data, home_path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		change_dir(data, get_env_var_value(data->env, "OLDPWD"));
		printf("%s\n", get_env_var_value(data->env, "PWD"));
		return (EXIT_SUCCESS);
	}
	change_dir(data, args[1]);
	return (EXIT_SUCCESS);
}