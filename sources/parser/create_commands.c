#include "minishell.h"

void	create_commands(t_data *data, t_token *token)
{
	t_token *temp;

	temp = token;
	if (temp->type == END)
		return;
	while (temp->next != NULL)
	{
		printf("temp actuel : TYPE : %d - STR : |%s|\n", temp->type, temp->str);
		// si c'est le début de la chaine de token, créer automatiquement un t_command
		if (temp == token)
			lst_add_back_cmd(&data->cmd, lst_new_cmd(false));	
		if (temp->type == WORD || temp->type == VAR)
			parse_word(&data->cmd, &temp);
		else if (temp->type == INPUT)
			parse_input(&data->cmd, &temp);
		else if (temp->type == TRUNC)
			parse_trunc(&data->cmd, &temp);
		//else if (temp->type == HEREDOC)
		 	//parse_heredoc(data, &temp);
		//else if (temp->type == APPEND)
		 	//parse_append(&data->cmd, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd, &temp);
		else if (temp->type == END)
			break;
		else
		{
			printf("\tTOKEN NOT PARSABLE YET: %s\n", temp->str);
			break;
		}
	}
	if (data->cmd->args)
	{
		int i = 0;
		while (data->cmd->args[i])
		{
			printf("BEFORE EXIT - Print args :\ni : %d - str : |%s|\n", i, data->cmd->args[i]);
			i++;
		}
	}
}