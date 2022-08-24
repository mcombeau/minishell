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
	while (temp->type == VAR && temp->next->type == VAR && temp->next->join == true)
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
**  a WORD or a VAR and if they are a VAR that has to be joined, we have 
**  to loop through all the tokens that check these conditions 
**  (type == VAR and join == true) before counting them as one argument
*/

int	count_args(t_token *temp)
{
	int i;

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

int	echo_mode(t_token **token_node, t_command *last_cmd)
{
	int nb_args;
	t_token	*temp;
	int i;

	temp = *token_node;
	nb_args = count_args(temp);
	printf("nb_args dans echo mode : %d\n", nb_args);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 1));
	if (!last_cmd->args)
		return (FAILURE);
	i = 0;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->join == true)
		{
			last_cmd->args[i] = join_vars(&temp);
			printf("je suis passé dans le join == true\n");
		}
		else
			last_cmd->args[i] = temp->str;
		printf("flags :\ni : %d - str : |%s|\n", i, last_cmd->args[i]);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

/*
**  This function fills the array of arguments of the last_cmd by default mode:
**    - It allocates the array of arguments thanks to the count_args function
**    - It loops through the tokens list while the nodes are of type
**        VAR or WORD, and fills last_cmd->args[i] with the current token 
*/

int	default_mode(t_token **token_node, t_command *last_cmd)
{
	int i;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	while (temp->type == WORD || temp->type == VAR)
	{
		i++;
		temp = temp->next;
	}
	last_cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!last_cmd->args)
		return (FAILURE);
	temp = *token_node;
	i = 0;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_cmd->args[i] = temp->str;
		printf("flags :\ni : %d - str : |%s|\n", i, last_cmd->args[i]);
		i++;
		temp = temp->next;
	}
    last_cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

/*
**  This function fills the arguments in the command structure (command->args)
**  It has two modes: 
**    - The "echo mode" if the command is the builtin "echo"
**    - The default mode for all the other cases
*/

int	fill_args(t_token	**token_node, t_command *last_cmd)
{
	if (!(ft_strcmp(last_cmd->command, "echo")))
	{
		if (echo_mode(token_node, last_cmd) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (default_mode(token_node, last_cmd) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}