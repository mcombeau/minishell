#include "minishell.h"

/* test_find_env_var:
*	Tests finding the correct index for a given variable in the
*	environment.
*/
void	test_find_env_var(void)
{
	int	idx;

	printf("\n\nSearching for index of var %s...\n", "HOME");
	idx = get_env_var_index("HOME");
	if (idx == -1)
		printf("Could not find %s in env.\n", "HOME");
	else
		printf("Found idx [%d] var: %s\n", idx, g_env_vars[idx]);
	printf("\n\nSearching for index of var %s...\n", "SHELL");
	idx = get_env_var_index("SHELL");
	if (idx == -1)
		printf("Could not find %s in env.\n", "SHELL");
	else
		printf("Found idx [%d] var: %s\n", idx, g_env_vars[idx]);
	printf("\n\nSearching for index of var %s...\n", "XDG");
	idx = get_env_var_index("XDG");
	if (idx == -1)
		printf("Could not find %s in env.\n", "XDG");
	else
		printf("Found idx [%d] var: %s\n", idx, g_env_vars[idx]);
	printf("\n\nSearching for index of var %s...\n", "/bin");
	idx = get_env_var_index("/bin");
	if (idx == -1)
		printf("Could not find %s in env.\n", "/bin");
	else
		printf("Found idx [%d] var: %s\n", idx, g_env_vars[idx]);
}

/* test_pwd:
*	Tests the pwd command. To test different pwds from main,
*	cd into another folder, then run the executable from there:
*	i.e. ./../../minishell/minishell
*	That should show the current working directory.
*/
void	test_pwd()
{
	sh_builtin_pwd();
}

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
	test_find_env_var();
	test_pwd();
}
