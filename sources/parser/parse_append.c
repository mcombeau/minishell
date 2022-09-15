#include "minishell.h"

/*
	***APPEND***
	Redirection of output in append mode causes the file whose name results 
	from the expansion of word to be opened for appending on file descriptor n, 
	or the standard output (fd 1) if n is not specified. 
	If the file does not exist it is created.

	The general format for appending output is: [n]>>word.

	Focus on the O_APPEND flag of the function open() :
	" O_APPEND
              The file is opened in append mode.  Before each write(2),
              the file offset is positioned at the end of the file, as
              if with lseek(2).  The modification of the file offset and
              the write operation are performed as a single atomic step."
*/

/**
 * When encountering a APPEND typed token ('>>'), this function :
 *  - sets the boolean cmd->iredir_out to TRUE
 * 	- If the next token is valid, it opens the output file (or creates
 * 	 it if it doesn't exist) with the correct relative path retrieved
 * 	 beforehand and appends the previous token(s) to the end of the
 * 	 output file.
 * 	- With the fd information, completes the necessary fields of 
 * 	  the command structure -> fd_out and potentially error and err_msg.
 *
 */
void	parse_append(t_command **last_cmd, t_token **token_lst)
{
	t_token	*temp;
	t_command	*first_cmd;
//	t_command	*cmd;
//	char	*file;
//	int		fd;

	temp = *token_lst;
	first_cmd = lst_first_cmd(*last_cmd);
//	cmd = lst_last_cmd(*last_cmd);
	printf("\tAdding outfile to io_fds: %s\n", temp->next->str);
	// Initialize input-output structure if it doesn't exist.
	init_io(first_cmd);
	// Set the output filename as outfile in the io_fds structure of the
	// first command in the list of commands.
	first_cmd->io_fds->outfile = ft_strdup(temp->next->str);
	// Mark outfile open mode as APPEND.
	first_cmd->io_fds->mode = APPEND;
	printf("\tDone setting cmd io file: %s\n", (*last_cmd)->io_fds->infile);

//	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPARSE - Parse_append function\n");
//	cmd->redir_out = true;
	// char *test = get_absolute_path(data->envp, temp->next->str);
	// printf("test : %s\n", test);
//	file = get_relative_path(temp->next->str);
//	fd = open(file, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
//	if (fd == -1)
//	{
//		cmd->error = errno;
//		cmd->err_msg = ft_strdup(strerror(errno));
//	}
//	cmd->io_fds->fd_out = fd;
//	free(file);
//	printf("Fd : %d\n", cmd->io_fds->fd_out);
//	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}