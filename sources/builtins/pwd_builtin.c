#include "minishell.h"

/* pwd_builtin:
*	Executes the builtin pwd command and displays the
*	current working directory path.
*/
void	pwd_builtin(void)
{
	int		idx;
	char	**pwd_var;

	idx = get_env_var_index("PWD");
	pwd_var = ft_split(g_env_vars[idx], '=');
	ft_putendl_fd(pwd_var[1], STDOUT_FILENO);
	idx = 0;
	while (pwd_var[idx])
	{
		free(pwd_var[idx]);
		idx++;
	}
	free(pwd_var);
}
