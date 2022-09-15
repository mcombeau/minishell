#include "minishell.h"

/*
	INPUT -> REDIR_IN (<)
	Redirection of input causes the file whose name results from the expansion 
	of word to be opened for reading on file descriptor n, or the standard input
	(file descriptor 0) if n is not specified.

	The general format for redirecting input is: [n]<word
	Source : https://www.gnu.org/software/bash/manual/bash.html#Redirections

	Exemple : sort < mylist.txt => on trie dans l'ordre alphabetique le contenu qui se
				trouve dans "mylist.txt".
				wc -l < test.txt => affiche le nb de lignes dans le fichier test
	
	Probleme car avec ECHO ça marche différemment :
https://unix.stackexchange.com/questions/63658/redirecting-the-content-of-a-file-to-the-command-echo)
*/

/*
static void	display_error(t_command *cmd, char *infile)
{
	cmd->error = errno;
	cmd->err_msg = ft_strdup(strerror(errno));
	printf("bash: %s: %s\n", infile, cmd->err_msg);
}*/

void	parse_input(t_command **last_cmd, t_token **token_lst)
{
	t_token	*temp;
	t_command	*cmd;
	t_command	*first_cmd;
//	char	*file;
//	int		fd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	first_cmd = lst_first_cmd(*last_cmd);
	if (cmd->command && ft_strcmp(cmd->command, "echo") == SUCCESS)
	{
		*token_lst = temp->next->next;
		return ;
	}
//	cmd->redir_in = true;
//	file = get_relative_path(temp->next->str);
	printf("\tAdding infile to io_fds: %s\n", temp->next->str);
	// Initialize input-output structure if it doesn't exist.
	init_io(first_cmd);
	// Set the input filename as infile in the io_fds structure of the
	// first command in the list of commands.
	first_cmd->io_fds->infile = ft_strdup(temp->next->str);
	printf("\tDone setting cmd io file: %s\n", (*last_cmd)->io_fds->infile);
//	fd = open(file, O_RDWR, S_IRWXU);
//	if (fd == -1)
//		display_error(cmd, temp->next->str);
//	cmd->io_fds->fd_in = fd;
//	free(file);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}