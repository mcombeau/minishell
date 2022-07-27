#include "minishell.h"

void	variable_check(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->str[i])
	{
		if ((*token_node)->str[i] == '$')
		{
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break;	
			(*token_node)->type = VAR;
			return ;
		}
		i++;
	}
}

void	quote_status(t_token **token_node)
{
	if ((*token_node)->str[0] == '\"')
		(*token_node)->status = DQUOTE;
	else if ((*token_node)->str[0] == '\'')
		(*token_node)->status = SQUOTE;
}

int	define_token(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		variable_check(&temp);
		quote_status(&temp);
		temp = temp->next;
	}
	//print_token(*token_lst);
	return (0);
}