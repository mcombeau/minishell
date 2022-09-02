/*
#include "minishell.h"

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
