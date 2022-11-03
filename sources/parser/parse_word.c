#include "minishell.h"

static bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

static void	split_var_cmd_token(t_command *last_cmd)
{
	t_token		*new_tokens;
	char		**strs;
	int			i;

	new_tokens = NULL;
	if (!contains_space(last_cmd->command))
		return ;
	strs = ft_split(last_cmd->command, ' ');
	if (!strs)
		return ;
	free_ptr(last_cmd->command);
	last_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = lst_new_token(strs[1], NULL, WORD, DEFAULT);
	i = 2;
	while (strs[i])
	{
		lst_add_back_token(&new_tokens, lst_new_token(strs[i], NULL, WORD, DEFAULT));
		i++;
	}
	lst_add_back_token(&new_tokens, lst_new_token(NULL, NULL, END, DEFAULT));
	fill_args(&new_tokens, last_cmd);
	free_str_tab(strs);
	lstclear_token(&new_tokens, &free_ptr);
}

void	parse_word(t_command **cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*last_cmd;

	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_cmd = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
			|| last_cmd->command == NULL)
		{
			last_cmd->command = ft_strdup(temp->str);
			if (temp->type == VAR && contains_space(last_cmd->command))
				split_var_cmd_token(last_cmd);
			temp = temp->next;
		}
		else
			fill_args(&temp, last_cmd);
	}
	*token_lst = temp;
}
