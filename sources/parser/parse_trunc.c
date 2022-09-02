#include "minishell.h"

/*
	TRUNC -> Redirection of output.
	The file whose name results from the expansion of word has to be opened 
    in writing mode on fd n or the standard output (fd 1) if n is not specified.
    If the file does not exist it is created;
    if it does exist it is truncated to 0 size.

	The general format for redirecting output is: [n]>[|]word
*/

// static char	*get_absolute_path(char **env, char *file_to_open)
// {
// 	char	*path;
// 	int		i;

// 	path = ft_strdup("PWD");
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strcmp(path, env[i]) == SUCCESS)
// 			break;
// 		i++;
// 	}
// 	path = ft_strjoin(*env + (i + 4), "/");
// 	path = ft_strjoin(path, file_to_open);
// 	printf("PARSING - Get_absolute_path function return : %s\n", path);
// 	return (path);
// }

static char	*get_relative_path(char *file_to_open)
{
	char *path;
	char *ret;

	path = ft_strdup("./");
	ret = ft_strjoin(path, file_to_open);
	printf("PARSING - Get_rel_path function return : %s\n", ret);
	return (ret);
}

/**
 * When encountering a TRUNC typed token ('>'), this function :
 * 	- sets the boolean command->redir_out to TRUE;
 * 	- If the next token is valid, it opens the output file (or creates
 * 	  it if it does not exist) with the correct relative path retrieved
 * 	  beforehand;
 * 	- With the fd information, completes the fields of 
 * 	  command structure : fd_out and potentially error and err_msg.
 */
void	parse_trunc(t_data *data, t_command **last_cmd, t_token **token_lst)
{
	t_token	*temp;
	t_command	*cmd;
	char	*file;
	int		fd;

	(void) data;
	temp = *token_lst;
	cmd = *last_cmd;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPARSE - Parse_redir_out function\n");
	cmd->redir_out = true;
	if (temp->next->type == WORD || temp->next->type == VAR)
	{
		// char *test = get_absolute_path(data->envp, temp->next->str);
		// printf("test : %s\n", test);
		file = get_relative_path(temp->next->str);
		fd = open(file, O_CREAT | O_RDWR, S_IRWXU);
		if (fd == -1)
		{
			cmd->error = errno;
			cmd->err_msg = ft_strdup(strerror(errno));
			cmd->io_fds->fd_out = 2;
			printf("N° d'erreur : %d - Erreur : %s - Fd : %d\n", cmd->error,\
		cmd->err_msg, cmd->io_fds->fd_out);
		}
		else
			cmd->io_fds->fd_out = fd;
		free(file);
	}
	// else // SYNTAX ERROR ex: echo hello > , ou echo hello > |
	// à mettre dans le lexer utils maybe ?
	printf("Fd : %d\n", cmd->io_fds->fd_out);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	*token_lst = temp->next->next;
}

/*

NOTES:
* Si on fait ls > test.txt puis echo hello > test.txt
le nouveau contenu va écraser le précédent

* cmd TRUNC OUTPUT_FILE word
exemple : grep test > test.txt test1.txt
-> si y a un word après l'OUTPUT_FILE il va dans le echo, pas dans la redir

*si line commence par un TRUNC (>) il faut creer la liste chainee, et faire condition 
existence cmd + fonction pour corriger ca

*/