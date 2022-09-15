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

int	erase_and_replace(t_token **token_node, char *str, char *var_value, int index)
{
	int i;
	int j;
	char *new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) *
		(ft_strlen(str) - var_length(str + index) + ft_strlen(var_value)));
	if (!new_str)
		return (1);
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
	free((*token_node)->str);
	(*token_node)->str = new_str;
	// printf("str dans le nod : %s\n", (*token_node)->str);
	return (0);
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
		if (erase_and_replace(token_node, (*token_node)->str, var_value, index) == 1)
		{
			free(var_value);
			return (1);
		}
	}
	free(var_value);
	return (0);
}