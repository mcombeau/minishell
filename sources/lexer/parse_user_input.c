/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:01:18 by alexa             #+#    #+#             */
/*   Updated: 2024/11/29 18:09:51 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * Another stupid Norminette bypass.
 * @brief	Updates the redirection type.
 * @param	token_str	A string of current token.
 * @param	redir_type	A pointer to the redirection type.
 */
static void	norminette_stuff_update_redir_type(const char *token_str,
	enum e_redir_type *redir_type)
{
	if (ft_strncmp(token_str, "<<", sizeof("<<") - 1) == 0
		|| ft_strncmp(token_str, "<", sizeof("<") - 1) == 0)
		*redir_type = STDIN_REDIR;
	else if (ft_strncmp(token_str, ">>", sizeof(">>") - 1) == 0
		|| ft_strncmp(token_str, ">", sizeof(">") - 1) == 0)
		*redir_type = STDOUT_REDIR;
	else
		*redir_type = NO_REDIR;
}

/**
 * Easily the most stupid Norminette bypass.
 * @brief	Checks if all redirections are followed by some file.
 * @param	data	Pointer to the main data structure.
 * @return	(SUCCESS) if all redirections are followed by some file.
 * 			(FAILURE) otherwise.
 */
static int	norminette_stupid_bypass_check_redirs(t_data *data)
{
	enum e_redir_type	redir_type;
	t_token				*current_token;

	redir_type = NO_REDIR;
	current_token = data->token;
	while (current_token != NULL)
	{
		if ((ft_strncmp(current_token->str, "<<", sizeof("<<") - 1) == 0
				|| ft_strncmp(current_token->str, "<", sizeof("<") - 1) == 0
				|| ft_strncmp(current_token->str, ">>", sizeof(">>") - 1) == 0
				|| ft_strncmp(current_token->str, ">", sizeof(">") - 1) == 0
				|| ft_strncmp(current_token->str, "|", sizeof("|") - 1) == 0)
			&& redir_type != NO_REDIR)
		{
			errmsg("expected the file before ", current_token->str, true);
			return (FAILURE);
		}
		norminette_stuff_update_redir_type(current_token->str, &redir_type);
		current_token = current_token->next;
	}
	return (SUCCESS);
}

/* parse_user_input:
*	Tokenizes and parses user input into a structure for execution.
*	Returns true if successful, false in case of error.
*/
bool	parse_user_input(t_data *data)
{
	if (data->user_input == NULL)
		exit_builtin(data, NULL);
	else if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	else if (input_is_space(data->user_input))
		return (true);
	add_history(data->user_input);
	if (tokenization(data, data->user_input) == FAILURE
		|| data->token->type == END || check_if_var(&data->token) == FAILURE
		|| norminette_stupid_bypass_check_redirs(data) == FAILURE)
		return (false);
	var_expander(data, &data->token);
	handle_quotes(data);
	create_commands(data, data->token);
	return (true);
}
