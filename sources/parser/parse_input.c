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
}
*/

/* open_infile:
*	Opens an infile. If an infile was already set, frees it
*	and overwrites it. If a previous infile open failed (file does
*	not exist or permission denied), does not open any further input file.
*	Ex.:
*		< Makefile <README.md cat > test
*			Uses contents of README as input (ignores Makefile)
*		< forbidden <README.md cat > test
*			Permission denied (no README cat)
*/
static void	open_infile(t_io_fds *io, char *file, char *original_filename)
{
	if (io->infile)
	{
		if (io->fd_in == -1)
			return ;
		free(io->infile);
		close(io->fd_in);
	}
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		errmsg_cmd("", original_filename, "ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		errmsg_cmd("", io->infile, strerror(errno), false);
}

void	parse_input(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
//	if (cmd->command && ft_strcmp(cmd->command, "echo") == SUCCESS)
//	{
//		*token_lst = temp->next->next;
//		return ;
//	}
	init_io(cmd);
	open_infile(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
