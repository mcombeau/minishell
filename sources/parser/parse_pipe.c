#include "minishell.h"

// ex : echo  bonjour | wc -l
	/*
		une commande deja cree : pour echo bonjour
		on arrive au pipe : on doit creer une nouvelle commande
		puis creer une aure commande
	*/
void	parse_pipe(t_command **cmd, t_token **token_lst)
{
	t_command *temp;
	t_command *last_cmd;
	
	temp = lst_last_cmd(*cmd);
	// Marquer pipe_output sur la commande avant de créer la prochaine
	temp->pipe_output = true;
	// Create the pipe cmd
//	lst_add_back_cmd(cmd, lst_new_cmd(true));
	
	// Raccorder les nodes de la cmd précédente avec la cmd pipe
	last_cmd = lst_last_cmd(*cmd);
	temp->next = last_cmd;
	last_cmd->prev = temp;
	last_cmd->next = NULL;

	// Puis créer une autre commande pour la prochaine commande 
	lst_add_back_cmd(&last_cmd, lst_new_cmd(false));
    *token_lst = (*token_lst)->next;
	
	// et faire un last cmd
}