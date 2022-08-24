#include "minishell.h"

/*
 *      These functions fill the cmd structure with token_str and if the cmd
 *      is a builtin, set the bool builtin to true.
 * 
 */
void	fill_cmd(t_command *last_cmd, char *token_str)
{
	last_cmd->command = token_str;
	if (ft_strcmp("echo", token_str)
		|| ft_strcmp("cd", token_str)
		|| ft_strcmp("pwd", token_str)
		|| ft_strcmp("export", token_str)
		|| ft_strcmp("unset", token_str)
		|| ft_strcmp("env", token_str)
		|| ft_strcmp("exit", token_str))
		last_cmd->is_builtin = true;
}

void	parse_word(t_data *data, t_token **token_lst)
{
	t_token	*temp;
	t_command	*last_cmd;

	temp = *token_lst;
	lst_add_back_cmd(&data->cmd, lst_new_cmd(false));
	last_cmd = lst_last_cmd(data->cmd);
	while (temp->type == WORD || temp->type == VAR)
	{
		printf("je suis dans la boucle de parse_word\n");
		printf("temp : %d, temp de next : %d\n", temp->type, temp->next->type);
		// si c'est le premier c'est forcement la commande
		if (temp == *token_lst)
		{
			fill_cmd(last_cmd, temp->str);
			printf("La cmd filled : %s\n", last_cmd->command);
			temp = temp->next;
		}
		else
			fill_args(&temp, last_cmd);
		//&temp = (*temp)->next;
		
	}
	*token_lst = temp;
	// *token_lst = (*token_lst)->next;
}