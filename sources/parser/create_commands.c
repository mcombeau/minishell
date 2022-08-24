#include "minishell.h"

void	create_commands(t_data *data, t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp->next != NULL)
	{
		printf("temp actuel : TYPE : %d - STR : |%s|\n", temp->type, temp->str);
		if (temp->type == WORD || temp->type == VAR)
			parse_word(data, &temp);
		else if (temp->type == PIPE || temp->type == END)
			break;
		// 	parse_pipe(data, &temp);
		// else if (temp->type == INPUT)
		// 	parse_input(data, &temp);
		// else if (temp->type == TRUNC)
		// 	parse_trunc(data, &temp);
		// else if (temp->type == HEREDOC)
		// 	parse_heredoc(data, &temp);
		// else if (temp->type == APPEND)
		// 	parse_append(data, &temp);
	}
}