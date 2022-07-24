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
#define YELLOW	"\e[33m"
#define BLUE	"\e[34m"
#define PURPLE	"\e[35m"
#define CYAN	"\e[36m"
#define GREY	"\e[37m"

static t_command *basic_parse(char *input)
{
	t_command	*cmd;
	char		**cmd_args;

	cmd_args = ft_split(input, ' ');
	if (!cmd_args)
		exit_shell(errmsg("test", input, "Could not split args", 0));
	cmd = malloc(sizeof * cmd);
	if (!cmd)
		exit_shell(errmsg("test", "malloc", strerror(errno), errno));
	cmd->command = cmd_args[0];
	cmd->args = cmd_args;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->pipe = false;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	return(cmd);
}

void	test_execute(char *input)
{
	t_command	*cmd;

	cmd = basic_parse(input);
	execute(cmd);
}

static void	test_invalid_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                     BASIC INVALID TEST                            |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s does_not_exist\n", BCYAN, NC);
	test_execute("does_not_exist");
	printf("\n%stest input >%s README.md\n", BCYAN, NC);
	test_execute("README.md");
	printf("\n%stest input >%s blah/hello\n", BCYAN, NC);
	test_execute("blah/hello");
}

static void	test_localbin_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                     BASIC LOCAL BIN TEST                          |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s /usr/bin/who\n", BCYAN, NC);
	test_execute("/usr/bin/who");
//	printf("\n%stest input >%s ./minishell\n", BCYAN, NC);
//	test_execute("./minishell");
}

static void	test_sysbin_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                     BASIC SYS/BIN TEST                            |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s ls\n", BCYAN, NC);
	test_execute("ls");
	printf("\n%stest input >%s ls -la\n", BCYAN, NC);
	test_execute("ls -la");
	printf("\n%stest input >%s cat README.md\n", BCYAN, NC);
	test_execute("cat README.md");
}

static void	test_builtin_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                      BASIC BULTIN TEST                            |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s pwd\n", BCYAN, NC);
	test_execute("pwd");
	printf("\n%stest input >%s cd ..\n", BCYAN, NC);
	test_execute("cd ..");
	printf("\n%stest input >%s pwd\n", BCYAN, NC);
	test_execute("pwd");
	printf("\n%stest input >%s cd minishell\n", BCYAN, NC);
	test_execute("cd minishell");
	printf("\n%stest input >%s pwd\n", BCYAN, NC);
	test_execute("pwd");
	printf("\n%stest input >%s export friday=13\n", BCYAN, NC);
	test_execute("export friday=13");
	is_var_in_env("friday");
	printf("\n%stest input >%s exit 42 21\n", BCYAN, NC);
	test_execute("exit 42 21");

}

void	test_execution(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", "\e[7;36m", NC);
	printf(  "%s|                                                                   |%s\n", "\e[7;36m", NC);
	printf(  "%s|                    START EXECUTION TESTS                          |%s\n", "\e[7;36m", NC);
	printf(  "%s|                                                                   |%s\n", "\e[7;36m", NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", "\e[7;36m", NC);
	test_builtin_exec();
	test_sysbin_exec();
	test_localbin_exec();
	test_invalid_exec();
}