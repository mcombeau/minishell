#include "minishell.h"

void	free_data (t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	lstclear_token(&data->token, &free);
}