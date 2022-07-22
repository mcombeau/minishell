#include "minishell.h"

int	init_data(t_data *data, char **env)
{
	data->env = env;
	data->token = NULL;
	return (0);
}