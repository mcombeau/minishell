#include "minishell.h"

/* text_env:
*	A basic test to check if the global g_env_vars variable
*	defined in minishell.h is correctly initialized. 
*/
void	test_env(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (!init_env(env))
	{
		printf("Test env: global environment variable not initialized!\n");
		exit_shell();
	}
	sh_builtin_env();
}
