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
	new_node->join = false;
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

void	lstdelone_token(t_token *lst, void (*del)(void *))
{
	if (del && lst && lst->str)
	{	
		(*del)(lst->str);
		lst->str = NULL;
	}
	free(lst);
}

void	lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		lstdelone_token(*lst, del);
		*lst = tmp;
	}
}

t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*tmp;
	tmp = *head;

	printf("HEAD : |%s|\n", (*head)->str);
	printf("TO_DEL : |%s|\n", to_del->str);
	printf("INSERT : |%s|\n", insert->str);
	if (tmp == NULL)
		*head = insert;
	else if (tmp == to_del)
	{
		*head = insert;
		insert->next = tmp->next;
		if (tmp->next != NULL)
			tmp->next->prev = insert;
	}
	else
	{
		while (tmp != to_del)
			tmp = tmp->next;
		insert->prev = tmp->prev;
		tmp->prev->next = insert;
		while (insert->next)
			insert = insert->next;
		tmp->next->prev = insert;
		insert->next = tmp->next;
	}
	free(to_del->str);
	free(to_del);
	return (insert);
}

void	print_token(t_token *lst)
{
	t_token *temp;
	int i = 0;
	
	printf("lst = %p\n", lst);
	temp = lst;
	while (temp)
	{
		printf("NODE : %d - TYPE : %d - STATE : %d - Str: |%s|\n", i, temp->type, temp->status, temp->str);
		printf("----------------------------------------------------------\n");
		temp = temp->next;
		i++;
	}
}
