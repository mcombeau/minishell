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

char	*get_relative_path(char *file_to_open)
{
	char	*path;
	char	*ret;

	if (file_to_open[0] == '/')
		return (ft_strdup(file_to_open));
	path = ft_strdup("./");
	ret = ft_strjoin(path, file_to_open);
	printf("PARSING - Get_rel_path function return : %s\n", ret);
	return (ret);
}

/* open_outfile_trunc:
*	Opens an outfile in truncated mode. If an outfile was already set, frees it
*	and overwrites it. If a previous infile or outfile open failed (file does
*	not exist or permission denied), does not open any further output file.
*
*	Ex.:
*		echo hello > forbidden_file > test
*		echo hello >> forbidden_file > test
*		< forbidden_file cat > test
*	In these 3 cases, the test file should not be opened or created.
*/
static void	open_outfile_trunc(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
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
void	parse_trunc(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_outfile_trunc(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
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