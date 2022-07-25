#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include "libft.h"

/******************************************************************************
*								MACROS										  *
******************************************************************************/

# define PROMPT "\033[0;35m➜\033[0;m \033[0;33mMinishell >\033[0;m "
# define CMD_NOT_FOUND -42

# define TRUE 0
# define FALSE 1

/******************************************************************************
*							GLOBAL VARIABLE									  *
******************************************************************************/
extern char	**g_env_vars;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct	s_token 
{	
	char			*str;
	int				type;
	int				status;
	struct s_token	*prev;
	struct s_token	*next;
}               t_token;

typedef struct	s_data
{
	t_token	*token;
	char	*user_input;
	char	**cmd_tab;
	char	**env;

}				t_data;

/* io_fds structure:
*	Contains infile and outfile fds as well as
*	backup of the stdin and stdout fds. Each command
*	will have a pointer to this structure but only
*	the first and last command will really use it.
*/
typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	int		mode;	//Append? Heredoc?
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
} t_io_fds;

/* NOTES about command structure:
*	- pipe bool: set as true only if the output of this
*		command is piped to the next command. Set false if
*		the input of this command comes from the output of
*		the previous command.
*	- args: should contain command name as arg[0].
*/
typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

/******************************************************************************
*								ENUMS									      *
******************************************************************************/

enum token_types {
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum quoting_status {
    DEFAULT,
    SQUOTE,
    DQUOTE
};

/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/

/* ------------------------ ERROR & EXIT HANDLING ---------------------------*/
// exit.c
void	exit_shell(t_command *cmd_list, int	exno);

// error.c
int		errmsg(char *command, char *detail, char *error_message, int error_nb);
void	free_str_array(char **strs);

// cleanup.c
void	free_str_array(char **strs);
void	free_env_vars(void);
void	free_cmd_list(t_command *cmd_list);

/* ------------------------ PARSING -----------------------------------------*/
// tokenize.c
int     tokenization(t_data *data, char *str);

// lexer_utils.c
int		check_consecutives(t_token **token_lst);

// define_tokens.c
int		define_token(t_token **token_lst);

// token_lst_utils.c
t_token	*lst_new_token(char *str, int type, int status);
void	lst_add_back_token(t_token **alst, t_token *new_node);
void	print_token(t_token *lst);

//init_data.c
int		init_data(t_data *data, char **env);

/* ------------------------ EXECUTION ---------------------------------------*/
// env.c
bool	init_env(char **env);
int		env_var_count(char **env);
int		get_env_var_index(char *var);
char	*get_env_var_value(char *var);
bool	is_valid_env_var_key(char *var);

// env_set.c
bool	set_env_var(char *key, char *value);
bool	remove_env_var(int idx);

// builtins
int		env_builtin(char **args);
int		pwd_builtin(char **args);
int		echo_builtin(char **args);
int		export_builtin(char **args);
int		unset_builtin(char **args);
int		cd_builtin(char **args);
int		exit_builtin(char **args);

// signal.c
void	handle_signal(int signo);

// execute.c
int		execute(t_command *cmds);

// parse_path.c
char	*get_cmd_path(char *cmd);

// pipe.c
bool	create_pipes(t_command *cmd_list);
bool	set_pipe_fds(t_command *cmds, t_command *curr_cmd);
void	close_pipe_fds(t_command *cmds, t_command *skip_cmd);
void	close_fds(t_command *cmds);

// file_io.c
bool	open_infile_outfile(t_io_fds *io);
bool	restore_io(t_io_fds *io);

/* ------------------------ TESTING -----------------------------------------*/
// test.c
void	test_minishell(int ac, char **av);
void	test_builtins(void);
void	test_execution(void);
void 	is_var_in_env(char *arg);

#endif