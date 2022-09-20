#include "minishell.h"

// ex : echo  bonjour | wc -l
	/*
		une commande deja cree : pour echo bonjour
		on arrive au pipe : on doit creer une nouvelle commande
		puis creer une aure commande
	*/
void	parse_pipe(t_command **cmd, t_token **token_lst)
{
	t_command	*temp;
	t_command	*last_cmd;

	temp = lst_last_cmd(*cmd);
	temp->pipe_output = true;
	lst_add_back_cmd(&last_cmd, lst_new_cmd(false));
	*token_lst = (*token_lst)->next;
}
