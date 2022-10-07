#include "minishell.h"

void	print_cmd_list(t_data *data)
{
	t_command *cmd;

	cmd = data->cmd;
	printf("\n---- COMMAND LIST\n");
	while (cmd)
	{
		printf("--- Command = %s\n", cmd->command);
		if (cmd->args)
		{
			for (int i = 0; cmd->args[i]; i++)
			printf("\tArgs[%d] = %s\n", i, cmd->args[i]);
		}
		printf("\tPipe_output = %d\n", cmd->pipe_output);
		if (cmd->io_fds)
		{
			if (cmd->io_fds->infile)
			{
				printf("\tInfile: %s\n", cmd->io_fds->infile);
				printf("\t\tfd_in: %d\n", cmd->io_fds->fd_in);
			}
			if (cmd->io_fds->heredoc_delimiter)
				printf("\tHeredoc delimiter: %s\n", cmd->io_fds->heredoc_delimiter);
			if (cmd->io_fds->outfile)
			{
				printf("\tOutfile: %s\n", cmd->io_fds->outfile);
				printf("\t\tfd_in: %d\n", cmd->io_fds->fd_out);
			}
		}
		if (cmd->prev == NULL)
			printf("\tprev = NULL\n");
		else
			printf("\tprev = %s\n", cmd->prev->command);
		if (cmd->next == NULL)
			printf("\tnext = NULL\n");
		else
			printf("\tnext = %s\n", cmd->next->command);
		printf("\n");
		cmd = cmd->next;
	}
	printf("\n");
}
