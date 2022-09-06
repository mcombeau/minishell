#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
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

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define FAILURE 1

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
	bool			join;
	struct s_token	*prev;
	struct s_token	*next;
}               t_token;

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
*	- pipe_output bool: set as true only if the output of this
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
	bool				pipe_output;
	bool				is_builtin;
	bool				is_pipe;
	bool				redir_out;
	bool				redir_in;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	int					error;
	char				*err_msg;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct	s_data
{
	t_token		*token;
	char		*user_input;
	char		**cmd_tab;
	char		**env;
	t_command	*cmd;

}				t_data;

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
void	close_fds(t_command *cmds, bool close_backups);
void	free_str_array(char **strs);
void	free_env_vars(void);
void	free_cmd_list(t_command *cmd_list);

/* ------------------------ LEXER -----------------------------------------*/
// tokenize.c
int     tokenization(t_data *data, char *str);

// lexer_utils.c
int		check_consecutives(t_token **token_lst);

// check_if_var.c
int		check_if_var(t_token **token_lst);

// token_lst_utils.c
t_token	*lst_new_token(char *str, int type, int status);
void	lst_add_back_token(t_token **alst, t_token *new_node);
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);
void	lstdelone_token(t_token *lst, void (*del)(void *));
void	lstclear_token(t_token **lst, void (*del)(void *));
void	print_token(t_token *lst);

//var_tokenization.c
int		var_tokenization(t_data *data);

/* ------------------------ EXPANSION ---------------------------------------*/
//expander.c
int		var_expander(t_data *data, t_token **token_lst);

//recover_value.c
char	*recover_val(char *str, t_data *data);

//identify_var.c
char	*identify_var(char *str);
int		var_length(char *str);
bool	is_var_compliant(char c);

//replace_var.c
int		replace_var(t_token **token_node, char *var_value, int index);
int		erase_and_replace(t_token **token_node, char *str, char *var_value, int index);
void	copy_var_value(char *new_str, char *var_value, int *j);
int		erase_var(t_token **token_node, char *str, int index);


/* ------------------------ PARSER ---------------------------------------*/
//quotes_handler.c
int	 	handle_quotes(t_data *data);
bool	quotes_in_string(char *str);
int		count_len(char *str, int count, int i);

//quotes_remover.c
int		remove_quotes(t_token **token_node);

//create_command.c
void	create_commands(t_data *data, t_token *token);

//parse_command.c
void	parse_word(t_command **cmd, t_token **token_lst);

//fill_arguments.c
int		fill_args(t_token	**token_node, t_command *last_cmd);
int		count_args(t_token *temp);
char	*join_vars(t_token **token_node);
int	add_args_default_mode(t_token **token_node, t_command *last_cmd);
int	create_args_default_mode(t_token **token_node, t_command *last_cmd);
int	add_args_echo_mode(t_token **token_node, t_command *last_cmd);
int	create_args_echo_mode(t_token **token_node, t_command *last_cmd);

//cmd_lst_utils.c
t_command	*lst_new_cmd(bool value);
void	lst_add_back_cmd(t_command **alst, t_command *new_node);
void	lst_delone_cmd(t_command *lst, void (*del)(void *));
void	lst_clear_cmd(t_command **lst, void (*del)(void *));
t_command	*lst_last_cmd(t_command *cmd);
void	free_tab(char **tab);


//parse_trunc.c
void	parse_trunc(t_command **last_cmd, t_token **token_lst);
char	*get_relative_path(char *file_to_open);

//parse_input.c
void	parse_input(t_command **last_cmd, t_token **token_lst);

//parse_append.c
void	parse_append(t_command **last_cmd, t_token **token_lst);

//parse_pipec
void	parse_pipe(t_command **cmd, t_token **token_lst);

//init_data.c
int		init_data(t_data *data, char **env);

//free_data.c
void	free_data (t_data *data);
void	free_data_2 (t_data *data);

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