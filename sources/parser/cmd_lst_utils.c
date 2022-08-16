#include "minishell.h"

t_command	*lst_new_cmd(bool value)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	new_node->is_pipe = value;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}


void	lst_add_back_cmd(t_command **alst, t_command *new_node)
{
	t_command	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

void	lst_delone_cmd(t_command *lst, void (*del)(void *))
{
	(void)(*del);
	// if (del && lst)
	// 	(*del)(lst->infos);
	// boucle speciale pour free les doubles tableaux
		// (*del)(lst->flags);
		// (*del)(lst->arg_env);
	// ATTENTION : peut etre close les fd ici
	free(lst);
}

void	lst_clear_cmd(t_command **lst, void (*del)(void *))
{
	t_command	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		lst_delone_cmd(*lst, del);
		*lst = temp;
	}
}

t_command	*lst_last_cmd(t_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}