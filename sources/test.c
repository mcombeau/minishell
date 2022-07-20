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
	printf("Testing pwd:\n");
	pwd_builtin();
	printf("Removing PWD from env and testing pwd:\n");
	remove_env_var(get_env_var_index("PWD"));
	pwd_builtin();
}

void	test_echo()
{
	char	**args;
	int		i;

	args = ft_split("-n Oh boy hello world !", ' ');
	echo_builtin(args);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = ft_split("Oh boy hello world !", ' ');
	echo_builtin(args);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = ft_split("Oh boy hello world !", '.');
	echo_builtin(args);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = ft_split("\"-n\" Oh boy hello world !", '.');
	echo_builtin(args);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = ft_split("-n Oh boy \'hello\' world !", '.');
	echo_builtin(args);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/* test_add_env_var:
*	Tests adding a new variable to the environment.
*/
void	test_add_env_var(void)
{
	int	start_var_count;
	int	mid_var_count;
	int	end_var_count;

	start_var_count = env_var_count(g_env_vars);
	set_env_var("BLABLA", "1234");
	set_env_var("USERNAME", "Hello World !!!!!");
	set_env_var("bob", NULL);
	set_env_var("bob", "hello");
	set_env_var("bob", "alice");
	set_env_var("BLABLA", "bla1bla2bla3");
	set_env_var("crickets", "this is a stupid env var");
	mid_var_count = env_var_count(g_env_vars);
	remove_env_var(get_env_var_index("BLABLA"));
	end_var_count = env_var_count(g_env_vars);
	env_builtin();
	printf("\n\nNumber of vars at start =\t%d\nNumber of vars at mid = \t%d\nNumber of vars at end = \t%d\n",
			start_var_count, mid_var_count, end_var_count);
}

/* text_env:
*	A basic test to check if the global g_env_vars variable
*	defined in minishell.h is correctly initialized. 
*/
void	test_execution(void)
{
//	env_builtin();
//	test_find_env_var();
	test_pwd();
//	(void)env;
//	test_echo();
//	test_add_env_var();
}
