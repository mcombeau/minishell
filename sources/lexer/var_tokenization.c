/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tokenization.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:13:43 by alexa             #+#    #+#             */
/*   Updated: 2022/09/19 13:38:08 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_word(char *str, int end, int start)
{
	char	*new_word;
	int		i;

	i = 0;
	new_word = malloc(sizeof(char) * (end - start + 1));
	if (!new_word)
		return (NULL);
	while (start < end)
	{
		new_word[i] = str[start];
		i++;
		start++;
	}
	new_word[i] = '\0';
	return (new_word);
}

static int	create_empty_str_in_new_node(t_token **token_lst, char *str_backup)
{
	char	*str;

	str = malloc(sizeof(char) * 1);
	if (!str)
		return (1);
	str[0] = '\0';
	lst_add_back_token(token_lst, lst_new_token(str, str_backup, VAR, DEFAULT));
	return (0);
}

static void	set_new_lst_to_true(t_token **new_lst)
{
	t_token	*temp;

	temp = *new_lst;
	while (temp)
	{
		temp->join = true;
		temp = temp->next;
	}
}

static t_token	*split_var(char *str, char *str_backup, t_token *token_lst)
{
	int		i;
	int		start;
	char	*new_word;

	i = 0;
	if (!str[i])
		create_empty_str_in_new_node(&token_lst, str_backup);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			start = i;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != ' ')
				i++;
		}
		new_word = copy_word(str, i, start);
		lst_add_back_token(&token_lst, lst_new_token(new_word, str_backup, VAR, DEFAULT));
	}
	return (token_lst);
}

int	var_tokenization(t_data *data)
{
	t_token	*temp;
	t_token	*new_lst;
	t_token	*token_lst;

	temp = data->token;
	new_lst = NULL;
	token_lst = NULL;
	while (temp)
	{
		if (temp->type == VAR)
		{
			new_lst = split_var(temp->str, temp->str_backup, token_lst);
			if (temp->join == true)
				set_new_lst_to_true(&new_lst);
			temp = insert_lst_between(&data->token, temp, new_lst);
		}
		temp = temp->next;
	}
	return (0);
}
