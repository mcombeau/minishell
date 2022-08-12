#include "minishell.h"

void	free_data (t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	lstclear_token(&data->token, &free);
}

void	free_data_2(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	if (data->token)
		lstclear_token(&data->token, &free);
	// free_t_pipe(data);
	rl_clear_history ();
}