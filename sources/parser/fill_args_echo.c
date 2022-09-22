#include "minishell.h"

/*
**  This function joins all the tokens of a quoted sentence
**  (ex " Hello $user") that was previously split.
**  To join them, the tokens have to be of type VAR and the join
**  setting must be set to true (the quotes are implied)
**  The function is only used when the command is "echo".
**  
**  ex: The strings -> "Hello" "  " "world"
**      become "Hello  world"
*/

char	*join_vars(t_token **token_node)
{
	t_token	*temp;
	char	*str;

	temp = *token_node;
	str = ft_strdup(temp->str);
	while (temp->type == VAR && temp->next->type == VAR
		&& temp->next->join == true)
	{
		str = ft_strjoin(str, temp->next->str);
		temp = temp->next;
	}
	*token_node = temp;
	return (str);
}

/*
**  This function counts the number of arguments in the list of tokens
**  To consider a token or multiple tokens as an argument they must be either
**  a WORD or a VAR and if they	temp = *token_node;
 are a VAR that has to be joined, we have
**  to loop through all the tokens that check these conditions 
**  (type == VAR and join == true) before counting them as one argument
*/

int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->type == VAR && temp->join == true)
		{
			while (temp->type == VAR && temp->join == true)
				temp = temp->next;
			i++;
		}
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

/*
**  This function deals with the specific case when the command is "echo"
**    - It allocates the array of arguments thanks to the count_args function
**    - It loops through the tokens list while the nodes are of type
**        VAR or WORD: 
**         * If "bool join = true" in the token structure is true : we join all
**           the tokens of type VAR that have the setting "join = true"
**         * if "join = false" we just fill the last_cmd_>args[i] 
**            with the current token.
*/

int	create_args_echo_mode(t_token **token_node, t_command *last_cmd)
{
	int		nb_args;
	t_token	*temp;
	int		i;

	temp = *token_node;
	nb_args = count_args(temp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->join == true)
			last_cmd->args[i] = join_vars(&temp);
		else
			last_cmd->args[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

static char	**copy_in_new_tab(
	int len, char **new_tab, t_command *last_cmd, t_token *tmp)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = last_cmd->args[i];
		i++;
	}
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
			new_tab[i] = join_vars(&tmp);
		else
			new_tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	add_args_echo_mode(t_token **token_node, t_command *last_cmd)
{
	int		len;
	int		nb_args;
	char	**new_tab;
	t_token	*temp;

	temp = *token_node;
	nb_args = count_args(temp);
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (nb_args + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_in_new_tab(len, new_tab, last_cmd, temp);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	temp = temp->next;
	*token_node = temp;
	return (SUCCESS);
}
