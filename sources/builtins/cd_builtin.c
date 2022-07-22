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
	if (!chdir(path))
	{
		set_env_var("OLDPWD", cwd);
		set_env_var("PWD", getcwd(buff, BUFSIZ));
	}
	else
	{
		if(access(path, F_OK) == -1)
			errmsg("cd", path, "No such file or directory", 1);
		else if (access(path, X_OK))
			errmsg("cd", path, "Permission denied", 1);
		else
			errmsg("cd", path, "Not a directory", 1);
		return (false);
	}
	return (true);
}

/* cd_builtin:
*	Executes the builtin cd command by changing the working directory.
*	Returns 1 on success, 0 on failure.
*/
bool	cd_builtin(char **args)
{
	char	*home_path;

	home_path = get_env_var_str("HOME");
	if (!args[0] || ft_strncmp(args[0], "--", 3) == 0)
		return (change_dir(home_path));
	if (args[1])
		return (errmsg("cd", NULL, "too many arguments", 0));
	if (ft_strncmp(args[0], "-", 2) == 0)
	{
		change_dir(get_env_var_str("OLDPWD"));
		printf("%s\n", get_env_var_str("PWD"));
		return (true);
	}
	change_dir(args[0]);
	return (true);
}