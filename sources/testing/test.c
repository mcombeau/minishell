#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"

#define NC		"\e[0m"

#define BGREY	"\e[1;30m"
#define BRED	"\e[1;31m"
#define BGREEN	"\e[1;32m"
#define BYELLOW	"\e[1;33m"
#define BBLUE	"\e[1;34m"
#define BPURPLE	"\e[1;35m"
#define BCYAN	"\e[1;36m"
#define BWHITE	"\e[1;37m"

#define BLACK	"\e[30m"
#define RED		"\e[31m"
#define GREEN	"\e[32m"
#define BROWN	"\e[33m"
#define BLUE	"\e[34m"
#define PURPLE	"\e[35m"
#define CYAN	"\e[36m"
#define GREY	"\e[37m"

static void is_var_in_env(char *arg)
{
	int		idx;
	char	*equal_sign;
	char	*check;

	if (!arg)
	{
		printf("%sVar %s cannot be in env.%s\n", RED, arg, NC);
		return ;
	}
	if ((equal_sign = ft_strchr(arg, '=')) != NULL)
		{
			idx = equal_sign - arg;
			check = ft_substr(arg, 0, idx);
		}
		else
			check = ft_strdup(arg);
		idx = get_env_var_index(check);
		free(check);
		if (idx != -1)
			printf("Var in env: [%s%s%s]\n", GREEN, g_env_vars[idx], NC);
		else
			printf("%sNo var with key [%s] in env.%s\n", RED, arg, NC);
}

static void	unit_test_env_var_index(char *arg)
{
	int	idx;

	printf("\nSearching for index of var %s...\n", arg);
	idx = get_env_var_index(arg);
	if (idx == -1)
		printf("%sCould not find %s in env.%s\n", RED, arg, NC);
	else
		printf("%sFound idx [%d] var: %s%s\n", GREEN, idx, g_env_vars[idx], NC);
}
/* test_find_env_var:
*	Tests finding the correct index for a given variable in the
*	environment.
*/
static void	test_find_env_var(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                        FIND ENV VAR                               |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);

	unit_test_env_var_index("HOME");
	unit_test_env_var_index("SHELL");
	unit_test_env_var_index("XDG");
	unit_test_env_var_index("/bin");
}

/* test_pwd:
*	Tests the pwd command. To test different pwds from main,
*	cd into another folder, then run the executable from there:
*	i.e. ./../../minishell/minishell
*	That should show the current working directory.
*/
static void	test_pwd()
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                              PWD                                  |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);

	printf("Testing pwd:\n");
	pwd_builtin(NULL);

	printf("\nRemoving PWD from env and testing pwd:\n");
	remove_env_var(get_env_var_index("PWD"));
	is_var_in_env("PWD");
	pwd_builtin(NULL);
}

static void	test_echo()
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                              ECHO                                 |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);

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

static void unit_test_set_env_var(char *key, char *val)
{
	printf("Before:\n");
	is_var_in_env(key);
	printf("\n%sSetting env var: key = \"%s\", value = \"%s\"%s\n", CYAN, key, val, NC);
	set_env_var(key, val);
	printf("\nAfter:\n");
	is_var_in_env(key);
}

static void	test_add_env_var(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                           SET ENV VAR                             |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);

	int	start_var_count;
	int	mid_var_count;
	int	end_var_count;
	
	start_var_count = env_var_count(g_env_vars);

	printf("====== TEST SET ENV 1 ==========\n");
	unit_test_set_env_var("BLABLA", "1234");
	printf("\n====== TEST SET ENV 2 ==========\n");
	unit_test_set_env_var("USERNAME", "Hello World !!!!!");
	printf("\n====== TEST SET ENV 3 ==========\n");
	unit_test_set_env_var("bob", NULL);
	printf("\n====== TEST SET ENV 4 ==========\n");
	unit_test_set_env_var("bob", "is your uncle");
	printf("\n====== TEST SET ENV 5 ==========\n");
	unit_test_set_env_var("bob", "alice");
	printf("\n====== TEST SET ENV 6 ==========\n");
	unit_test_set_env_var("crickets", "this is a stupid env var");
	
	mid_var_count = env_var_count(g_env_vars);

	printf("\n====== TEST SET ENV 7 ===========\n");
	printf("%sRemoving env var: key = \"%s\"%s\n", CYAN, "bob", NC);
	remove_env_var(get_env_var_index("bob"));
	is_var_in_env("bob");

	printf("\n====== TEST COUNTS ==============\n");
	end_var_count = env_var_count(g_env_vars);
	printf("\nNumber of vars before changes =\t%d\nNumber of vars after adds = \t%d\nNumber of vars after remove = \t%d\n",
			start_var_count, mid_var_count, end_var_count);
}

static void	unit_test_export(char *arg1, char *arg2)
{
	char	*args[3] = {arg1, arg2, NULL};

	printf("%sExporting: arg[0] = \"%s\", arg[1] = \"%s\"%s\n", CYAN, arg1, arg2, NC);
	export_builtin(args);
	is_var_in_env(arg1);
	is_var_in_env(arg2);
}

static void	test_export(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                             EXPORT                                |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);

	printf("====== TEST EXPORT 1 ==========\n");
	unit_test_export("hello=42", NULL);

	printf("\n====== TEST EXPORT 2 ==========\n");
	unit_test_export("_hello=145", "crickets=blabla");

	printf("\n====== TEST EXPORT 3 ==========\n");
	unit_test_export("Hello=OH BOY!!!!!", "long=loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong!");
	
	printf("\n====== TEST EXPORT 4 ==========\n");
	unit_test_export("=123", "123=42");

	printf("\n====== TEST EXPORT 5 ==========\n");
	unit_test_export("nachos", "tacos=");

	printf("\n====== TEST EXPORT 6 ==========\n");
	unit_test_export("Porcupine=45=butterfly", "glad=to=be=here=with=everyone=ever");

//	printf("\n====== TEST EXPORT : PRINT ENV ==========\e[34m\n");
//	env_builtin();
}

static void	unit_test_unset(char *arg1, char *arg2)
{
	char	*args[3] = {arg1, arg2, NULL};
	printf("Before:\n");
	is_var_in_env(arg1);
	is_var_in_env(arg2);
	printf("\n%sUnsetting: arg[0] = \"%s\", arg[1] = \"%s\"%s\n", CYAN, arg1, arg2, NC);
	unset_builtin(args);
	printf("\nAfter:\n");
	is_var_in_env(arg1);
	is_var_in_env(arg2);
}

static void	test_unset(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                             UNSET                                 |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);

	printf("\n====== TEST UNSET 1 ==========\n");
	unit_test_unset("Hello", "long");
	
	printf("\n====== TEST UNSET 2 ==========\n");
	unit_test_unset("xyz", "crickets=");

	printf("\n====== TEST UNSET 3 ==========\n");
	unit_test_unset("123", "789");

	printf("\n====== TEST UNSET 4 ==========\n");
	unit_test_unset("hello@you", "a*");

//	printf("\n====== TEST EXPORT : PRINT ENV ==========\e[34m\n");
//	env_builtin();
}

static void	unit_test_cd(char *arg1, char *arg2)
{
	char	*args[3] = {arg1, arg2, NULL};
	char	buf[BUFSIZ];

	if (arg2)
		printf("%sCD test: cd %s %s%s\n", CYAN, arg1, arg2, NC);
	else if (arg1)
		printf("%sCD test: cd %s%s\n", CYAN, arg1, NC);
	else
		printf("%sCD test: cd%s\n", CYAN, NC);

	if (cd_builtin(args))
	{
		printf("OLDPWD =\t%s\n", get_env_var_str("OLDPWD"));
		printf("GETCWD =\t%s\n", getcwd(buf, BUFSIZ));
		printf("PWD =\t\t%s\n", get_env_var_str("PWD"));
	}
}

static void	test_cd(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                               CD                                  |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);

	printf("===== TEST CD 1 ========\n");
	unit_test_cd("includes", NULL);

	printf("\n===== TEST CD 2 ========\n");
	unit_test_cd("../sources", NULL);

	printf("\n===== TEST CD 3 ========\n");
	unit_test_cd("includes", "crux");

	printf("\n===== TEST CD 4 ========\n");
	struct stat st = {0};
	if (stat("../sources/testing/forbidden", &st) == -1)
    	mkdir("../sources/testing/forbidden", 0000);
	unit_test_cd("../sources/testing/forbidden", NULL);

	printf("\n===== TEST CD 5 ========\n");
	unit_test_cd("../sources/testing/test.c", NULL);

	printf("\n===== TEST CD 6 ========\n");
	unit_test_cd(NULL, NULL);

	printf("\n===== TEST CD 7 ========\n");
	unit_test_cd("-", NULL);

	printf("\n===== TEST CD 8 ========\n");
	unit_test_cd("..", NULL);

	printf("\n===== TEST CD 9 ========\n");
	unit_test_cd("-", NULL);

	printf("\n===== TEST CD 10 =======\n");
	unit_test_cd("/var/log", NULL);

	printf("\n===== TEST CD 11 =======\n");
	unit_test_cd("/glob", NULL);
}

static void	unit_test_exit(char *arg1, char *arg2)
{
	char	*args[3] = {arg1, arg2, NULL};

	if (arg2)
		printf("%sexit test: exit %s %s%s\n", CYAN, arg1, arg2, NC);
	else if (arg1)
		printf("%sexit test: exit %s%s\n", CYAN, arg1, NC);
	else
		printf("%sexit test: exit%s\n", CYAN, NC);
	exit_builtin(args);
}

static void	test_exit(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                              EXIT                                 |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);

	// Comment tests one by one to test them all. Exit builtin
	// exits the shell before doing all tests, of course.
	// Use command 'echo $?' to view exit code after minishell test is done.

	// Should exit with exit code 2:

//	unit_test_exit("blabla", "21345");
	unit_test_exit("123a", NULL);

	// Should not exit:
	unit_test_exit("42", "21");
	
	// Should exit with provided exit code:
//	unit_test_exit("42", NULL);
}

/* text_env:
*	A basic test to check if the global g_env_vars variable
*	defined in minishell.h is correctly initialized. 
*/
void	test_execution(void)
{
	test_find_env_var();
	test_pwd();
	test_cd();
	test_echo();
	test_add_env_var();
	test_export();
	test_unset();
	test_exit();
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                       ALL TESTS COMPLETE                          |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
}
