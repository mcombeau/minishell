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

/* basic_parse_with_inout_files:
*	Fills a command structure with a very basic input containing
*	a command name and some options, as well as an input and output file.
*	Returns the created command. Exits the shell test in case of error.
*/
static t_io_fds *very_basic_inout_files(char *infile, char *outfile)
{
	t_io_fds	*io;

	io = malloc(sizeof * io);
	if (!io)
	{
		printf("ERROR malloc io\n");
		return (NULL);
	}
	io->fd_in = -1;
	io->fd_out = -1;
	if (infile)
		io->infile = ft_strdup(infile);
	else
		io->infile = NULL;
	if (outfile)
		io->outfile = ft_strdup(outfile);
	else
		io->outfile = NULL;
	io->mode = -1;
	io->stdin_backup = -1;
	io->stdout_backup = -1;
	return(io);
}

/* super_basic_parse:
*	Fills a command structure with a very basic input containing only
*	a command name and some options.
*	Returns the created command. Exits the shell test in case of error.
*/
static t_command *super_basic_parse(char *input)
{
	t_command	*cmd;
	char		**cmd_args;

	cmd_args = ft_split(input, ' ');
	if (!cmd_args)
		exit_shell(NULL, errmsg("test", input, "Could not split args", 0));
	cmd = malloc(sizeof * cmd);
	if (!cmd)
		exit_shell(NULL, errmsg("test", "malloc", strerror(errno), errno));
	cmd->command = cmd_args[0];
	cmd->args = cmd_args;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->io_fds = NULL;
	cmd->pipe = false;
	cmd->pipe_fd = NULL;
	return(cmd);
}

void	test_execute_inout_file(char *infile, char *input, char *outfile)
{
	t_command	*cmd;

	if (!input)
	{
		printf("ERROR: need input!\n");
		return ;
	}
	cmd = super_basic_parse(input);
	cmd->io_fds = very_basic_inout_files(infile, outfile);
	execute(cmd);
}

void	test_execute_multiple_inout_file(char *infile, char *input1, char *input2, char *input3, char *outfile)
{
	t_command	*cmd_first;
	t_command	*cmd_second;
	t_command	*cmd_third;

	if (!input1 || !input2)
		return ;
	cmd_first = super_basic_parse(input1);
	cmd_second = super_basic_parse(input2);
	cmd_first->next = cmd_second;
	cmd_second->prev = cmd_first;
	cmd_first->pipe = true;
	cmd_second->pipe = false;
	cmd_first->io_fds = very_basic_inout_files(infile, outfile);
	cmd_second->io_fds = cmd_first->io_fds;
	if (input3)
	{
		cmd_third = super_basic_parse(input3);
		cmd_second->next = cmd_third;
		cmd_third->prev = cmd_second;
		cmd_second->pipe = true;
		cmd_third->pipe = false;
		cmd_third->io_fds = cmd_first->io_fds;
	}
	execute(cmd_first);
}

/* test_execute_multiple:
*	Simulates two or three piped commands for testing purposes.
*	Each input must be a string of characters starting with the
*	command to execute followed by options separated by spaces.
*	Requires at least two commands in order to pipe.
*/
void	test_execute_multiple(char *input1, char *input2, char *input3)
{
	t_command	*cmd_first;
	t_command	*cmd_second;
	t_command	*cmd_third;

	if (!input1 || !input2)
		return ;
	cmd_first = super_basic_parse(input1);
	cmd_second = super_basic_parse(input2);
	cmd_first->next = cmd_second;
	cmd_second->prev = cmd_first;
	cmd_first->pipe = true;
	cmd_second->pipe = false;
	if (input3)
	{
		cmd_third = super_basic_parse(input3);
		cmd_second->next = cmd_third;
		cmd_third->prev = cmd_second;
		cmd_second->pipe = true;
		cmd_third->pipe = false;
	}
	execute(cmd_first);
}

/* test_execute_basic:
*	Simulates a simple non-piped command execution. Input must be
*	a string of characters starting with the command to execute
*	followed by options separated by spaces.
*/
void	test_execute_basic(char *input)
{
	t_command	*cmd;

	cmd = super_basic_parse(input);
	execute(cmd);
}

static void	test_basic_inout_file(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|              BASIC INPUT OUTPUT FILE TEST                         |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("%sNOTE:\tThese tests only test truncated outfiles.\n\tAnother test will be created for appended oufiles.%s\n\n", PURPLE, NC);
	
	printf("\n%stest input >%s < README.md sed s/e/XXX/g\n", BCYAN, NC);
	test_execute_inout_file("README.md", "sed s/e/XXX/g", NULL);

	printf("\n%stest input >%s < README.md sed s/e/.../g > result_outfile\n", BCYAN, NC);
	test_execute_inout_file("README.md", "sed s/e/.../g", "result_outfile");

	printf("\n%stest input >%s < result_outfile cat\n", BCYAN, NC);
	test_execute_inout_file("result_outfile", "cat", NULL);

	printf("\n%stest input >%s < README.md wc -l > result_outfile\n", BCYAN, NC);
	test_execute_inout_file("README.md", "wc -l", "result_outfile");

	printf("\n%stest input >%s cat result_outfile\n", BCYAN, NC);
	test_execute_basic("cat result_outfile");

	printf("\n%stest input >%s < README.md grep Work | wc -l > result_outfile\n", BCYAN, NC);
	test_execute_multiple_inout_file("README.md", "grep Work", "wc -l", NULL, "result_outfile");

	printf("\n%stest input >%s cat result_outfile\n", BCYAN, NC);
	test_execute_basic("cat result_outfile");

	printf("\n%stest input >%s < README.md grep # | sed s/t/.x./g | sed s/l/ooo/g > result_outfile\n", BCYAN, NC);
	test_execute_multiple_inout_file("README.md", "grep #", "sed s/t/.x./g", "sed s/l/ooo/g", "result_outfile");

	printf("\n%stest input >%s cat result_outfile\n", BCYAN, NC);
	test_execute_basic("cat result_outfile");

	unlink("result_outfile");
}

static void	test_pipe_invalid_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                     PIPE INVALID TEST                             |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s ls -la | not_a_command\n", BCYAN, NC);
	test_execute_multiple("ls -la", "not_a_command", NULL);
	printf("\n%stest input >%s not_a_command | ls -la\n", BCYAN, NC);
	test_execute_multiple("not_a_command", "ls -la", NULL);
	printf("\n%stest input >%s cat README.md | not_a_command | wc -l\n", BCYAN, NC);
	test_execute_multiple("cat README.md", "not_a_command", "wc -l");
	printf("\n%stest input >%s not_a_command | not_a_command | not_a_command\n", BCYAN, NC);
	test_execute_multiple("not_a_command", "not_a_command", "not_a_command");

}

static void	test_pipe_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                     PIPE BASIC TEST                               |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s ls -la\n", BCYAN, NC);
	test_execute_basic("ls -la");
	printf("\n%stest input >%s ls -la | wc -l\n", BCYAN, NC);
	test_execute_multiple("ls -la", "wc -l", NULL);
	printf("\n%stest input >%s cat README.md | grep Work\n", BCYAN, NC);
	test_execute_multiple("cat README.md", "grep Work", NULL);
	printf("\n%stest input >%s cat README.md | wc -l\n", BCYAN, NC);
	test_execute_multiple("cat README.md", "wc -l", NULL);
	printf("\n%stest input >%s cat README.md | sed s/e/.../g | sed s/m/XXX/g\n", BCYAN, NC);
	test_execute_multiple("cat README.md", "sed s/e/.../g", "sed s/m/XXX/g");
	printf("\n%stest input >%s cat README.md | grep # | wc -l\n", BCYAN, NC);
	test_execute_multiple("cat README.md", "grep #", "wc -l");
	printf("\n%stest input >%s pwd | wc -l\n", BCYAN, NC);
	test_execute_multiple("pwd", "wc -l", NULL);
	printf("\n%stest input >%s env | wc -l\n", BCYAN, NC);
	test_execute_multiple("env", "wc -l", NULL);
	printf("\n%stest input >%s env | grep PATH\n", BCYAN, NC);
	test_execute_multiple("env", "grep PATH", NULL);
	printf("\n%stest input >%s cat README.md | pwd\n", BCYAN, NC);
	test_execute_multiple("cat README.md", "pwd", NULL);
	printf("\n%stest input >%s /usr/bin/who | sed s/2/X/g\n", BCYAN, NC);
	test_execute_multiple("/usr/bin/who", "sed s/2/X/g", NULL);
}

static void	test_invalid_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                     BASIC INVALID TEST                            |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s does_not_exist\n", BCYAN, NC);
	test_execute_basic("does_not_exist");
	printf("\n%stest input >%s README.md\n", BCYAN, NC);
	test_execute_basic("README.md");
	printf("\n%stest input >%s blah/hello\n", BCYAN, NC);
	test_execute_basic("blah/hello");
}

static void	test_localbin_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                     BASIC LOCAL BIN TEST                          |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s /usr/bin/who\n", BCYAN, NC);
	test_execute_basic("/usr/bin/who");
//	printf("\n%stest input >%s ./minishell\n", BCYAN, NC);
//	test_execute_basic("./minishell");
}

static void	test_sysbin_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                     BASIC SYS/BIN TEST                            |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s ls\n", BCYAN, NC);
	test_execute_basic("ls");
	printf("\n%stest input >%s ls -la\n", BCYAN, NC);
	test_execute_basic("ls -la");
	printf("\n%stest input >%s cat README.md\n", BCYAN, NC);
	test_execute_basic("cat README.md");
}

static void	test_builtin_exec(void)
{
	printf("%s\n+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf(  "%s|                      BASIC BULTIN TEST                            |%s\n", BYELLOW, NC);
	printf(  "%s+-------------------------------------------------------------------+%s\n", BPURPLE, NC);
	printf("\n%stest input >%s pwd\n", BCYAN, NC);
	test_execute_basic("pwd");
	printf("\n%stest input >%s cd ..\n", BCYAN, NC);
	test_execute_basic("cd ..");
	printf("\n%stest input >%s pwd\n", BCYAN, NC);
	test_execute_basic("pwd");
	printf("\n%stest input >%s cd minishell\n", BCYAN, NC);
	test_execute_basic("cd minishell");
	printf("\n%stest input >%s pwd\n", BCYAN, NC);
	test_execute_basic("pwd");
	printf("\n%stest input >%s export friday=13\n", BCYAN, NC);
	test_execute_basic("export friday=13");
	is_var_in_env("friday");
	printf("\n%stest input >%s exit 42 21\n", BCYAN, NC);
	test_execute_basic("exit 42 21");
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
	test_pipe_exec();
	test_pipe_invalid_exec();
	test_basic_inout_file();
}