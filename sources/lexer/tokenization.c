#include "minishell.h"

int	save_separator(t_token **token_lst, char *str, int index, int type)
{
	int i;
	char *sep;

	i = 0;
	if (type == APPEND || type == HEREDOC)
	{
		sep = (char *)malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		while (i < 2)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, type, DEFAULT));
	}
	else
	{
		sep = (char *)malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		while (i < 1)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, type, DEFAULT));
	}
	return (0);
}

int	save_word(t_token **token_lst, char *str, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	lst_add_back_token(token_lst, lst_new_token(word, WORD, DEFAULT));
	return (0);
}

int	is_separator(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);	
}

int	set_status(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		status = SQUOTE;
	else if (str[i] == '\"' && status == DEFAULT)
		status = DQUOTE;
	else if (str[i] == '\'' && status == SQUOTE)
		status = DEFAULT;
	else if (str[i] == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

/**
*	This function divides the given string (user input) into two
*   types of tokens : words or separators (pipes, heredoc , etc)
*	It checks each char of the string and defines if it is a separator or 
*   a word and then saves the token in a linked list.
*   Also checks if there is an unclosed quote error and defines which
*   separators will be evaluated following the single or double quoting rules:
*   
*   -Without quotes, bash tries to evaluate all special characters
*   -Single quotes (') prevent all evaluation
*   -Double quotes (") prevent most evaluation, but notably not the evaluation of variables
*
**/

int	tokenization(t_data *data, char *str)
{
	int	i;
	int end;
	int start;
	int	type;
	int	status;

	i = 0;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
		{
			type = is_separator(str, i);
			if (type) 
			{
				if (i != 0 && is_separator(str, i - 1) == 0)
					save_word(&data->token, str, i, start);
				if (type == APPEND || type == HEREDOC || type == PIPE
					|| type == INPUT || type == TRUNC || type == END)
				{
					save_separator(&data->token, str, i, type);
					if (type == APPEND || type == HEREDOC)
						i++;
				}
				start = i + 1;
			}
		}
		i++;
	}
	if (status != DEFAULT)
	{
		printf("Syntax error : the quotes are unclosed\n");
		return (1);
	}
	return (0);
}
