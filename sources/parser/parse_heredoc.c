#include "minishell.h"

//TODO: check if several heredocs can be opened at the same time.
//		heredoc might also be able to be opened after a pipe. Check for that too.
void	parse_heredoc(t_data *data, t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*first_cmd;
	t_io_fds	*io;

	temp = *token_lst;
	first_cmd = *last_cmd;
	init_io(first_cmd);
	io = first_cmd->io_fds;
	io->infile = ft_strdup("/tmp/.minishell_heredoc");
	io->heredoc_delimiter = ft_strdup(temp->next->str);
	if (get_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
