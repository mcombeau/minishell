#include "minishell.h"

int	erase_var(t_token **token_node, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_length(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + var_length(str + index) + 1; 
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free((*token_node)->str);
	(*token_node)->str = new_str;
	// printf("str dans le node : %s\n", (*token_node)->str);
	return (0);
}

void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

// Changed return type from int to char * to adapt the function
// to work for heredoc variable expansion. Heredoc has no tokens so token_node
// becomes optional.
// Heredoc variant replace_str_heredoc calls this function with token_node == NULL!
char	*erase_and_replace(t_token **token_node, char *str, char *var_value, int index)
{
	int i;
	int j;
	char *new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) *
		(ft_strlen(str) - var_length(str + index) + ft_strlen(var_value)));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			copy_var_value(new_str, var_value, &j);
			i = i + var_length(str + index) + 1;
			if (str[i] == '\0')
				break ;	
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	if (token_node && *token_node)
	{
		free((*token_node)->str);
		(*token_node)->str = new_str;
		// printf("str dans le nod : %s\n", (*token_node)->str);
	}
	return (new_str);
}

int	replace_var(t_token **token_node, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (erase_var(token_node, (*token_node)->str, index) == 1)
		{
			free(var_value);
			return (1);
		}
	}
	else
	{
		if (erase_and_replace(token_node, (*token_node)->str, var_value, index) == NULL)
		{
			free(var_value);
			return (1);
		}
	}
	free(var_value);
	return (0);
}

/* replace_str_heredoc:
*	Heredoc variant of replace_var, replaces an environment variable
*	by its value. Ex. $USER -> username.
*	Returns the replaced string.
*/
char *replace_str_heredoc(char *str, char *var_value, int index)
{
	char *tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = erase_and_replace(NULL, str, var_value, index);
		free(tmp);
	}
	free(var_value);
	return (str);
}