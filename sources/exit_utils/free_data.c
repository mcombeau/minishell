#include "minishell.h"

void	free_data(t_data *data, bool clear_history)
{
	if (data->user_input)
		free(data->user_input);
	if (data->token)
		lstclear_token(&data->token, &free);
	if (data->cmd)
	{
		if (data->cmd->io_fds)
			free_io(data->cmd->io_fds);
		lst_clear_cmd(&data->cmd, &free);
	}
	if (clear_history == true)
		rl_clear_history ();
}