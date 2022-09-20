/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:45:35 by alexa             #+#    #+#             */
/*   Updated: 2022/09/20 16:49:00 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	consecutive_ops(t_token *token_node)
{
	if (token_node->next)
	{
		if (token_node->type >= PIPE && token_node->next->type == END)
			return (TRUE);
		if (token_node->type >= PIPE && token_node->next->type == PIPE)
			return (TRUE);
		if ((token_node->type >= PIPE && token_node->next->type == PIPE)
			&& token_node->next->type != END)
			return (TRUE);
		if (token_node->type > PIPE && token_node->prev && token_node->prev->type > PIPE)
			return (TRUE);
		if (token_node->type > PIPE && token_node->next
			&& (token_node->next->type != WORD
				&& token_node->next->type != VAR))
			return (TRUE);
	}
	return (FALSE);
}

int	check_consecutives(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp && temp->next && temp->next->type != END)
		temp = temp->next;
	while (temp)
	{
		if (consecutive_ops(temp) == TRUE)
		{
			if (temp->next->type == END && temp->type > PIPE && temp->prev && temp->prev->type <= PIPE)
				errmsg("Syntax error near unexpected token ", "newline", true);
//			else if (temp->next->type == END && temp->type == PIPE)
//				errmsg("Syntax error near unexpected token ", temp->str, true);
			else
				errmsg("Syntax error near unexpected token ", temp->str, true);
			return (FAILURE);
		}
//		temp = temp->next;
		temp = temp->prev;
	}
	return (SUCCESS);
}
