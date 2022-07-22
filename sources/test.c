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

void	test_export(void)
{
	char	**args;
	int		idx;

	args = ft_calloc(3, sizeof * args);

	printf("====== TEST EXPORT 1 ==========\n");
	args[0] = ft_strdup("Hello=42");
	args[1] = ft_strdup("\0");
	args[3] = NULL;
	printf("\e[31mExporting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	export_builtin(args);
	idx = get_env_var_index("Hello");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);
	
	printf("\n====== TEST EXPORT 2 ==========\n");
	args[0] = ft_strdup("_hello=145");
	args[1] = ft_strdup("crickets=blabla");
	args[3] = NULL;
	printf("\e[31mExporting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	export_builtin(args);
	idx = get_env_var_index("_hello");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);
	idx = get_env_var_index("crickets");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);

	printf("\n====== TEST EXPORT 3 ==========\n");
	args[0] = ft_strdup("Hello=OH BOY!!!!!");
	args[1] = ft_strdup("long=loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong!");
	args[3] = NULL;
	printf("\e[31mExporting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	export_builtin(args);
	idx = get_env_var_index("Hello");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);
	idx = get_env_var_index("long");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);

	printf("\n====== TEST EXPORT 4 ==========\n");
	args[0] = ft_strdup("=123");
	args[1] = ft_strdup("123=42");
	args[3] = NULL;
	printf("\e[31mExporting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	export_builtin(args);
	idx = get_env_var_index("");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);
	idx = get_env_var_index("123");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);

	printf("\n====== TEST EXPORT 5 ==========\n");
	args[0] = ft_strdup("nachos");
	args[1] = ft_strdup("tacos=");
	args[3] = NULL;
	printf("\e[31mExporting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	export_builtin(args);
	idx = get_env_var_index("nachos");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);
	idx = get_env_var_index("tacos");
	if (idx != -1)
		printf("Exported var in env: [%s]\n", g_env_vars[idx]);

	printf("\n====== TEST EXPORT 6 ==========\n");
	args[0] = ft_strdup("Porcupine=45=butterfly");
	args[1] = ft_strdup("glad=to=be=here=with=everyone=ever");
	args[3] = NULL;
	printf("\e[31mExporting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	export_builtin(args);
	idx = get_env_var_index("Porcupine");
	if (idx != -1)
	printf("Exported var in env: [%s]\n", g_env_vars[idx]);
	idx = get_env_var_index("glad");
	if (idx != -1)
	printf("Exported var in env: [%s]\n", g_env_vars[idx]);

	printf("\n====== TEST EXPORT : PRINT ENV ==========\e[34m\n");
	env_builtin();
	printf("\e[0m");
	int i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	test_unset(void)
{
	char	**args;
	int		idx;

	args = ft_calloc(3, sizeof * args);

	printf("\n====== TEST UNSET 1 ==========\n");
	args[0] = ft_strdup("Hello");
	args[1] = ft_strdup("long");
	args[3] = NULL;
	printf("\e[31mUnsetting: arg[0] = \"%s\", arg[1] = \"%s\"\e[0m\n", args[0], args[1]);
	idx = get_env_var_index(args[0]);
	if (idx != -1)
		printf("\e[36mVar \"%s\" exists in env: [%s]\e[0m\n", args[0], g_env_vars[idx]);
	else
		printf("\e[36mVar \"%s\" does not exist in env.\e[0m\n", args[0]);
	idx = get_env_var_index(args[1]);
	if (idx != -1)
		printf("\e[36mVar \"%s\" exists in env: [%s]\e[0m\n", args[1], g_env_vars[idx]);
	else
		printf("\e[36mVar \"%s\" does not exist in env.\e[0m\n", args[1]);
	unset_builtin(args);
	idx = get_env_var_index(args[0]);
	if (idx != -1)
		printf("Unset: Var \"%s\" exists in env: [%s]\n", args[0], g_env_vars[idx]);
	else
		printf("Unset: Var \"%s\" does not exist in env.\n", args[0]);
	idx = get_env_var_index(args[1]);
	if (idx != -1)
		printf("Unset: Var \"%s\" exists in env: [%s]\n", args[1], g_env_vars[idx]);
	else
		printf("Unset: Var \"%s\" does not exist in env.\n", args[1]);

	
	printf("\n====== TEST UNSET 2 ==========\n");
	args[0] = ft_strdup("xyz");
	args[1] = ft_strdup("crickets=");
	args[3] = NULL;
	printf("\e[31mUnsetting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	idx = get_env_var_index(args[0]);
	if (idx != -1)
		printf("\e[36mVar \"%s\" exists in env: [%s]\e[0m\n", args[0], g_env_vars[idx]);
	else
		printf("\e[36mVar \"%s\" does not exist in env.\e[0m\n", args[0]);
	idx = get_env_var_index(args[1]);
	if (idx != -1)
		printf("\e[36mVar \"%s\" exists in env: [%s]\e[0m\n", args[1], g_env_vars[idx]);
	else
		printf("\e[36mVar \"%s\" does not exist in env.\e[0m\n", args[1]);
	unset_builtin(args);
	idx = get_env_var_index(args[0]);
	if (idx != -1)
		printf("Unset: Var \"%s\" exists in env: [%s]\n", args[0], g_env_vars[idx]);
	else
		printf("Unset: Var \"%s\" does not exist in env.\n", args[0]);
	idx = get_env_var_index(args[1]);
	if (idx != -1)
		printf("Unset: Var \"%s\" exists in env: [%s]\n", args[1], g_env_vars[idx]);
	else
		printf("Unset: Var \"%s\" does not exist in env.\n", args[1]);

	printf("\n====== TEST UNSET 3 ==========\n");
	args[0] = ft_strdup("_123");
	args[1] = ft_strdup("789");
	args[3] = NULL;
	printf("\e[31mUnsetting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	idx = get_env_var_index(args[0]);
	if (idx != -1)
		printf("\e[36mVar \"%s\" exists in env: [%s]\e[0m\n", args[0], g_env_vars[idx]);
	else
		printf("\e[36mVar \"%s\" does not exist in env.\e[0m\n", args[0]);
	idx = get_env_var_index(args[1]);
	if (idx != -1)
		printf("\e[36mVar \"%s\" exists in env: [%s]\e[0m\n", args[1], g_env_vars[idx]);
	else
		printf("\e[36mVar \"%s\" does not exist in env.\e[0m\n", args[1]);
	unset_builtin(args);
	idx = get_env_var_index(args[0]);
	if (idx != -1)
		printf("Unset: Var \"%s\" exists in env: [%s]\n", args[0], g_env_vars[idx]);
	else
		printf("Unset: Var \"%s\" does not exist in env.\n", args[0]);
	idx = get_env_var_index(args[1]);
	if (idx != -1)
		printf("Unset: Var \"%s\" exists in env: [%s]\n", args[1], g_env_vars[idx]);
	else
		printf("Unset: Var \"%s\" does not exist in env.\n", args[1]);

	printf("\n====== TEST UNSET 4 ==========\n");
	args[0] = ft_strdup("hello@you");
	args[1] = ft_strdup("a*");
	args[3] = NULL;
	printf("\e[31mUnsetting: arg[0] = \"%s\", arg[1] = \"%s\"\n\e[0m", args[0], args[1]);
	idx = get_env_var_index(args[0]);
	if (idx != -1)
		printf("\e[36mVar \"%s\" exists in env: [%s]\e[0m\n", args[0], g_env_vars[idx]);
	else
		printf("\e[36mVar \"%s\" does not exist in env.\e[0m\n", args[0]);
	idx = get_env_var_index(args[1]);
	if (idx != -1)
		printf("\e[36mVar \"%s\" exists in env: [%s]\e[0m\n", args[1], g_env_vars[idx]);
	else
		printf("\e[36mVar \"%s\" does not exist in env.\e[0m\n", args[1]);
	unset_builtin(args);
	idx = get_env_var_index(args[0]);
	if (idx != -1)
		printf("Unset: Var \"%s\" exists in env: [%s]\n", args[0], g_env_vars[idx]);
	else
		printf("Unset: Var \"%s\" does not exist in env.\n", args[0]);
	idx = get_env_var_index(args[1]);
	if (idx != -1)
		printf("Unset: Var \"%s\" exists in env: [%s]\n", args[1], g_env_vars[idx]);
	else
		printf("Unset: Var \"%s\" does not exist in env.\n", args[1]);

	printf("\n====== TEST EXPORT : PRINT ENV ==========\e[34m\n");
	env_builtin();
	printf("\e[0m");

	int i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	test_cd(void)
{
	char	**args;
	char	buf[BUFSIZ];

	printf("===== TEST CD 1 ========\n");
	args = calloc(3, sizeof *args);
	args[0] = ft_strdup("includes");
	args[1] = NULL;
	args[2] = NULL;
	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}

	printf("===== TEST CD 2 ========\n");
	args[0] = ft_strdup("../sources");
	args[1] = NULL;
	args[2] = NULL;
	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}

	printf("===== TEST CD 3 ========\n");
	args[0] = ft_strdup("includes");
	args[1] = ft_strdup("crux");
	args[2] = NULL;
	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}

	printf("===== TEST CD 4 ========\n");
	args[0] = NULL;
	args[1] = NULL;
	args[2] = NULL;
	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}

	printf("===== TEST CD 5 ========\n");
	args[0] = ft_strdup("-");
	args[1] = NULL;
	args[2] = NULL;
	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}

	printf("===== TEST CD 6 ========\n");
	args[0] = ft_strdup("..");
	args[1] = NULL;
	args[2] = NULL;
	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}

	printf("===== TEST CD 7 ========\n");
	args[0] = ft_strdup("-");
	args[1] = NULL;
	args[2] = NULL;
	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}

	printf("===== TEST CD 8 ========\n");
	args[0] = ft_strdup("/var/log");
	args[1] = NULL;
	args[2] = NULL;
	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}
}

/* text_env:
*	A basic test to check if the global g_env_vars variable
*	defined in minishell.h is correctly initialized. 
*/
void	test_execution(void)
{
//	env_builtin();
//	test_find_env_var();
//	test_pwd();
//	(void)env;
//	test_echo();
//	test_add_env_var();
//	test_export();
//	test_unset();
	test_cd();
}
