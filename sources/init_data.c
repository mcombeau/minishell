#include "minishell.h"

int	init_data(t_data *data, char **env)
{
	data->env = env;
	data->token = NULL;
	return (SUCCESS);
}

void	init_io(t_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->mode = 0;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}