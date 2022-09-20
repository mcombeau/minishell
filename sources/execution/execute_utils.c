#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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