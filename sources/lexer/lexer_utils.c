/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:45:35 by alexa             #+#    #+#             */
/*   Updated: 2022/09/15 23:45:43 by alexa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	consecutive_ops(t_token *token_node)
{
	if (token_node->next)
	{
		if (token_node->type >= 4 && token_node->next->type == PIPE)
			return (TRUE);
		if ((token_node->type >= 4 && token_node->next->type == PIPE)
			&& token_node->next->type != END)
			return (TRUE);
		if (token_node->type >= 4 && token_node->next
			&& (token_node->next->type != WORD
				&& token_node->next->type != VAR))
			return (TRUE);
		if (token_node->type >= 4 && token_node->next->type == END)
			return (TRUE);
	}
	return (FALSE);
}

int	check_consecutives(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (consecutive_ops(temp) == TRUE)
		{
			errmsg("Syntax error near unexpected token", temp->str, true);
			return (FAILURE);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
