/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:14:16 by mcombeau          #+#    #+#             */
/*   Updated: 2022/10/05 17:45:44 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"

/******************************************************************************
*								MACROS										  *
******************************************************************************/
# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

//# define TRUE 1
//# define FALSE 0

# define SUCCESS 0
# define FAILURE 1

/******************************************************************************
*							GLOBAL VARIABLE									  *
******************************************************************************/
extern int	g_last_exit_code;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct s_token
{	
	char			*str;
	char			*str_backup;
	int				type;
	int				status;
	bool			join;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

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
	char	*heredoc_delimiter;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}	t_io_fds;

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
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	bool		interactive;
	t_token		*token;
	char		*user_input;
	char		**cmd_tab;
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	t_command	*cmd;
	pid_t		pid;
}	t_data;

/******************************************************************************
*								ENUMS									      *
******************************************************************************/

enum e_token_types {
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

enum e_quoting_status {
	DEFAULT,
	SQUOTE,
	DQUOTE
};

/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/

/* ------------------------ INITIALIZATION ----------------------------------*/
//init_data.c
bool		init_data(t_data *data, char **env);
void		init_io(t_command *cmd);

/* ------------------------ ERROR & EXIT HANDLING ---------------------------*/
// exit.c
void		exit_shell(t_data *data, int exno);

// error.c
int			errmsg_cmd(char *command, char *detail, char *error_message,
				int error_nb);
void		errmsg(char *errmsg, char *detail, int quotes);
bool		usage_message(bool return_val);
void		free_str_array(char **strs);

// cleanup.c
void		close_fds(t_command *cmds, bool close_backups);
void		free_str_array(char **strs);
void		free_io(t_io_fds *io);

//free_data.c
void		free_data(t_data *data, bool clear_history);

/* ------------------------ LEXER -----------------------------------------*/
// tokenization.c
int			tokenization(t_data *data, char *str);

//tokenization_utils.c
int			save_word_or_sep(int *i, char *str, int start, t_data *data);
int			set_status(int status, char *str, int i);
int			is_separator(char *str, int i);
int			save_word(t_token **token_lst, char *str, int index, int start);
int			save_separator(t_token **token_lst, char *str, int index, int type);

// lexer_grammar.c
int			check_consecutives(t_token **token_lst);

// check_if_var.c
int			check_if_var(t_token **token_lst);

// token_lst_utils.c
t_token		*lst_new_token(char *str, char *str_backup, int type, int status);
void		lst_add_back_token(t_token **alst, t_token *new_node);
void		lstdelone_token(t_token *lst, void (*del)(void *));
void		lstclear_token(t_token **lst, void (*del)(void *));
t_token		*insert_lst_between(t_token **head, t_token *to_del,
				t_token *insert);

//var_tokenization.c
int			var_tokenization(t_data *data);

/* ------------------------ EXPANSION ---------------------------------------*/
//expander.c
int			var_expander(t_data *data, t_token **token_lst);

//recover_value.c
char		*recover_val(char *str, t_data *data);

//identify_var.c
char		*identify_var(char *str);
int			var_length(char *str);
bool		is_var_compliant(char c);

//replace_var.c
int			replace_var(t_token **token_node, char *var_value, int index);
char		*erase_and_replace(t_token **token_node, char *str, char *var_value,
				int index);
void		copy_var_value(char *new_str, char *var_value, int *j);
int			erase_var(t_token **token_node, char *str, int index);
char		*var_expander_heredoc(t_data *data, char *str);
char		*replace_str_heredoc(char *str, char *var_value, int index);

//quotes_handler.c
int			handle_quotes(t_data *data);
bool		quotes_in_string(char *str);
int			count_len(char *str, int count, int i);

//quotes_remover.c
int			remove_quotes(t_token **token_node);

/* ------------------------ PARSER ---------------------------------------*/

//create_command.c
void		create_commands(t_data *data, t_token *token);

//parse_command.c
void		parse_word(t_command **cmd, t_token **token_lst);

//fill_arguments.c
int			fill_args(t_token	**token_node, t_command *last_cmd);
int			count_args(t_token *temp);
char		*join_vars(t_token **token_node);
int			add_args_default_mode(t_token **token_node, t_command *last_cmd);
int			create_args_default_mode(t_token **token_node, t_command *last_cmd);
int			add_args_echo_mode(t_token **token_node, t_command *last_cmd);
int			create_args_echo_mode(t_token **token_node, t_command *last_cmd);

//cmd_lst_utils.c
t_command	*lst_new_cmd(bool value);
void		lst_add_back_cmd(t_command **alst, t_command *new_node);
void		lst_delone_cmd(t_command *lst, void (*del)(void *));
void		lst_clear_cmd(t_command **lst, void (*del)(void *));
t_command	*lst_last_cmd(t_command *cmd);
t_command	*lst_first_cmd(t_command *cmd);
void		free_tab(char **tab);

//parse_trunc.c
void		parse_trunc(t_command **last_cmd, t_token **token_lst);
char		*get_relative_path(char *file_to_open);

//parse_input.c
void		parse_input(t_command **last_cmd, t_token **token_lst);

//parse_append.c
void		parse_append(t_command **last_cmd, t_token **token_lst);

//parse_heredoc.c
void		parse_heredoc(t_data *data, t_command **last_cmd,
				t_token **token_lst);

//parse_pipec
void		parse_pipe(t_command **cmd, t_token **token_lst);

/* ------------------------ EXECUTION ---------------------------------------*/
// env.c
int			env_var_count(char **env);
int			get_env_var_index(char **env, char *var);
char		*get_env_var_value(char **env, char *var);
bool		is_valid_env_var_key(char *var);

// env_set.c
bool		set_env_var(t_data *data, char *key, char *value);
bool		remove_env_var(t_data *data, int idx);

// builtins
int			env_builtin(t_data *data, char **args);
int			pwd_builtin(t_data *data, char **args);
int			echo_builtin(t_data *data, char **args);
int			export_builtin(t_data *data, char **args);
int			unset_builtin(t_data *data, char **args);
int			cd_builtin(t_data *data, char **args);
int			exit_builtin(t_data *data, char **args);

// signal.c
void		ignore_sigquit(void);
void		set_interactive_signal_trap(void);
void		set_noninteractive_signal_trap(void);

// execute.c
int			execute(t_data *data);

// execute_cmd.c
int			execute_command(t_data *data, t_command *cmd);
int			execute_builtin(t_data *data, t_command *cmd);

// execute_utils.c
bool		cmd_is_dir(char *cmd);
int			check_command_not_found(t_data *data, t_command *cmd);

// parse_path.c
char		*get_cmd_path(t_data *data, char *cmd);

// pipe.c
bool		create_pipes(t_data *data);
bool		set_pipe_fds(t_command *cmds, t_command *curr_cmd);
void		close_pipe_fds(t_command *cmds, t_command *skip_cmd);

// file_io.c
bool		check_infile_outfile(t_io_fds *io);
bool		redirect_io(t_io_fds *io);
bool		restore_io(t_io_fds *io);

// heredoc.c
bool		get_heredoc(t_data *data, t_io_fds *io);

/* ------------------------ DEBUG -------------------------------------------*/
// debug.c
void		print_cmd_list(t_data *data);

#endif