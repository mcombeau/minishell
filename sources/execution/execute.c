/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:09:49 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/19 18:22:42 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

/* get_children:
*	Waits for children to terminate after cleaning up fds and the command
*	list.
*	Returns a child's exit status as bash does:
*		"The return status (see Exit Status) of a simple command is its
*		exit status as provided by the POSIX 1003.1 waitpid function, or
*		128+n if the command was terminated by signal n."
*/
static int	get_children(t_data *data)
{
	int			status;

	close_fds(data->cmd, false);
	while (waitpid(-1, &status, 0) != -1 || errno != ECHILD)
		continue ;
	if (WIFEXITED(status))
		g_last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_code = 128 + WTERMSIG(status);
	else
		g_last_exit_code = status;
	return (g_last_exit_code);
}

/* check_cmd_list:
*	Checks if the list of commands to execute is valid.
*	Returns true if it is, false if it is not.
*/
static bool	check_cmd_list(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (cmd == NULL || cmd->command == NULL)
		return (false);
	while (cmd)
	{
/*		if (!ft_strcmp(cmd->command, "exit") && (cmd->prev != NULL || cmd->next != NULL))
		{
			if (cmd->prev && cmd->next)
			{
				cmd->prev->next = cmd->next;
				cmd->next->prev = cmd->prev;
			}
			else if (cmd->prev && !cmd->next)
			{
				cmd->prev->next = NULL;
				if (cmd->prev->pipe_output == 1)
					cmd->prev->pipe_output = 0;
			}
			else if (!cmd->prev && cmd->next)
			{
				data->cmd = cmd->next;
				cmd->next->prev = NULL;
			}
			lst_delone_cmd(cmd, &free);
		}
		else*/ if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
	return (true);
}

/* execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate. If the command is a builtin
*	and its output is not piped to another command, it is not forked.
*	Returns the exit code of the last child to terminate.
*/
int	execute(t_data *data)
{
	t_command	*cmd;
	int			pid;
	int			ret;

	ret = CMD_NOT_FOUND;
	cmd = data->cmd;
	if (!check_cmd_list(data))
		return (ret);
	if (!create_pipes(data) || !check_infile_outfile(data))
		return (1);
	print_cmd_list(data);
	pid = -1;
	while (pid != 0 && cmd)
	{
		if (!cmd->pipe_output && !cmd->prev)
		{
			redirect_io(cmd->io_fds);
			ret = execute_builtin(data, cmd);
			restore_io(cmd->io_fds);
		}
		if (ret != CMD_NOT_FOUND)
			return (ret);
		pid = fork();
		if (pid == -1)
			errmsg_cmd("fork", NULL, strerror(errno), errno);
		else if (pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}
