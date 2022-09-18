#include "minishell.h"

/*
 *      These functions fill the cmd structure with token_str and if the cmd
 *      is a builtin, set the bool builtin to true.
 * 
 */

void	parse_word(t_command **cmd, t_token **token_lst)
{
	t_token	*temp;
	t_command	*last_cmd;

	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		printf("je suis dans la boucle de parse_word\n");
		printf("temp : %d, temp de next : %d\n", temp->type, temp->next->type);
		last_cmd = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE) || last_cmd->command == NULL)
		{	
			last_cmd->command = temp->str;
			printf("La cmd filled : %s\n", last_cmd->command);
			temp = temp->next;
		}
		else
			fill_args(&temp, last_cmd);
	}
	*token_lst = temp;
}