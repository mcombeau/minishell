#include "minishell.h"

/* pwd_builtin:
*	Executes the builtin pwd command and displays the
*	current working directory path.
*/
void	pwd_builtin(void)
{
	char	buf[BUFSIZ];

	ft_putendl_fd(getcwd(buf, BUFSIZ), STDOUT_FILENO);
}
