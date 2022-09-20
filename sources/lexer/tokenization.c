/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:31:15 by alexa             #+#    #+#             */
/*   Updated: 2022/09/20 12:31:43 by alexa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	This function divides the given string (user input) into two
*   types of tokens : words or separators (pipes, heredoc , etc)
*	It checks each char of the string and defines if it is a separator or 
*   a word and then saves the token in a linked list.
*   Also checks if there is an unclosed quote error and defines which
*   separators will be evaluated following the single or double quoting rules:
*   
*   -Without quotes, bash tries to evaluate all special characters
*   -Single quotes (') prevent all evaluation
*   -Double quotes (") prevent most evaluation,
*		but notably not the evaluation of variables
*
*/

int	tokenization(t_data *data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
			start = save_word_or_sep(&i, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (status == SQUOTE)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}
