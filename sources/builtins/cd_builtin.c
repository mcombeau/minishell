#include "minishell.h"

bool	cd_builtin(char **args)
{
	if (args[1])
		return (errmsg("cd", NULL, "too many arguments", false));

	return (true);
}