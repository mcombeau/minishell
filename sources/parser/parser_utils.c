#include "minishell.h"

t_token	*lst_new_token(char *str, int type, int status)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!(new_node))
		return (NULL);
	new_node->str = str;
	new_node->type = type;
	new_node->status = status;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}


void	lst_add_back_token(t_token **alst, t_token *new_node)
{
	t_token	*start;

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