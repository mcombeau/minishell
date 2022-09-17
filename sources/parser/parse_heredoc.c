#include "minishell.h"

void	parse_heredoc(t_command **last_cmd, t_token **token_lst)
{
	printf("\n--- Parse heredoc.\n");
	t_token	*temp;
	t_command	*first_cmd;
//	t_command	*cmd;
//	char	*file;
//	int		fd;

	temp = *token_lst;
	first_cmd = *last_cmd;
//	cmd = lst_last_cmd(*last_cmd);
	printf("\tAdding outfile to io_fds: %s\n", temp->next->str);
	// Initialize input-output structure if it doesn't exist.
	init_io(first_cmd);
	// Set the input filename as infile in the io_fds structure of the
	// first command in the list of commands.
	first_cmd->io_fds->infile = ft_strdup("/tmp/.minishell_heredoc");
	// Set the delimiter :
	first_cmd->io_fds->heredoc_delimiter = ft_strdup(temp->next->str);
	// Mark outfile open mode as HEREDOC.
//	first_cmd->io_fds->out_mode = HEREDOC;
	printf("\tDone setting cmd io file: %s\n", (*last_cmd)->io_fds->outfile);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
/*
void	parse_heredoc(t_data *data, t_token **token_lst)
{
	(void)data;
	t_token	*temp;
	char	*line;
	char	*delimiter;

	temp = *token_lst;
	line = malloc(sizeof(char));
	delimiter = temp->next->str;
	while (line)
	{
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!(ft_strncmp(line, delimiter, (ft_strlen(line) - 1))))
			break;
	}
	free(line);
	temp = temp->next->next;
	*token_lst = temp;
}
*/
