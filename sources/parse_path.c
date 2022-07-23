#include "minishell.h"

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
			errmsg("malloc", NULL, "an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return(cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = ft_split(get_env_var_value("PATH"), ':');
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_str_array(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(cmd, env_paths);
	if (!cmd_path)
	{
		free(cmd);
		free_str_array(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
