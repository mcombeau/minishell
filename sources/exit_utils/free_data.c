#include "minishell.h"

void	free_data(t_data *data, bool clear_history)
{
	if (data->user_input)
		free(data->user_input);
	if (data->token)
		lstclear_token(&data->token, &free);
	if (data->cmd)
		lst_clear_cmd(&data->cmd, &free);
	if (clear_history == true)
	{
		if (data->env)
			free_tab(data->env);
		rl_clear_history();
	}
}