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
# include "libft.h"

/******************************************************************************
*								MACROS										  *
******************************************************************************/

# define PROMPT "\033[0;35m➜\033[0;m \033[0;33mMinishell >\033[0;m "

# define TRUE 0
# define FALSE 1

/******************************************************************************
*							GLOBAL VARIABLES								  *
******************************************************************************/
char	**g_env_vars;

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

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe;
	int					pipe_fds[2];
	int					fd_in;
	int					fd_out;
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

// exit.c
void	exit_shell(int	exno);

// error.c
int	errmsg(char *command, char *detail, char *error_message, int error_nb);

// env.c
bool	init_env(char **env);
int		env_var_count(char **env);
int		get_env_var_index(char *var);
char	*get_env_var_str(char *var);
bool	is_valid_env_var_key(char *var);

// env_set.c
bool	set_env_var(char *key, char *value);
bool	remove_env_var(int idx);

// builtins
bool	env_builtin(void);
void	pwd_builtin(void);
bool	echo_builtin(char **args);
bool	export_builtin(char **args);
bool	unset_builtin(char **args);
bool	cd_builtin(char **args);
void	exit_builtin(char **args);

// signal.c
void	handle_signal(int signo);

// test.c
void	test_execution(void);

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

#endif