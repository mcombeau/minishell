#include "minishell.h"

/* text_env:
*	A basic test to check if the global g_env_vars variable
*	defined in minishell.h is correctly initialized. 
*/
void	test_env(int ac, char **av, char **env)
{
	int	i;

	(void)ac;
	(void)av;
	if (!init_env(env))
		exit_shell();
	i = 0;
	while (g_env_vars[i])
	{
		printf("g_env_vars[%d] =\t%s\n", i, g_env_vars[i]);
		i++;
	}
}
