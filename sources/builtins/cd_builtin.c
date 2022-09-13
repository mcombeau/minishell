#include "minishell.h"

/* change_dir:
*	Changes the current working directory and updates the
*	OLDPWD environment variable.
*	Returns 1 on success, 0 on failure.
*/
static bool	change_dir(char	*path)
{
	char	*cwd;
	char	buff[BUFSIZ];

	cwd = getcwd(buff, BUFSIZ);
	if (chdir(path) == EXIT_SUCCESS)
	{
		set_env_var("OLDPWD", cwd);
		set_env_var("PWD", getcwd(buff, BUFSIZ));
	}
	else
	{
		errmsg("cd", path, strerror(errno), errno);
		return (false);
	}
	return (true);
}

/* cd_builtin:
*	Executes the builtin cd command by changing the working directory.
*	Returns 0 on success, 1 on failure.
*/
int	cd_builtin(char **args)
{
	char	*home_path;

	home_path = get_env_var_value("HOME");
	if (!args || !args[1] || ft_strncmp(args[1], "--", 3) == 0)
	{
		if (!home_path)
			return (errmsg("cd", NULL, "HOME not set", 0));
		return (!change_dir(home_path));
	}
	if (args[2])
		return (errmsg("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		change_dir(get_env_var_value("OLDPWD"));
		printf("%s\n", get_env_var_value("PWD"));
		return (EXIT_SUCCESS);
	}
	change_dir(args[1]);
	return (EXIT_SUCCESS);
}