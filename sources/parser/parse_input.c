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

void	parse_input(t_command **last_cmd, t_token **token_lst)
{
	t_token	*temp;
	t_command	*cmd;
	char	*file;
	int		fd;

	temp = *token_lst;
	cmd = *last_cmd;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPARSE - Parse_redir_in function\n");
	if (cmd->command && ft_strcmp(cmd->command, "echo") == SUCCESS)
	{
		printf("Fd in : %d - Fd out : %d\n", cmd->io_fds->fd_in, cmd->io_fds->fd_out);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		*token_lst = temp->next->next;
		return ;
	}
	cmd->redir_in = true;
	file = get_relative_path(temp->next->str);
	fd = open(file, O_CREAT | O_RDWR, S_IRWXU);
	if (fd == -1)
	{
		cmd->error = errno;
		cmd->err_msg = ft_strdup(strerror(errno));
		cmd->io_fds->fd_out = 2;
		printf("N° d'erreur : %d - Erreur : %s - Fd in : %d - Fd out : %d\n",
		cmd->error, cmd->err_msg,  cmd->io_fds->fd_in, cmd->io_fds->fd_out);
	}
	else
		cmd->io_fds->fd_in = fd;
	free(file);
	printf("Fd in : %d\n", cmd->io_fds->fd_in);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	*token_lst = temp->next->next;
}