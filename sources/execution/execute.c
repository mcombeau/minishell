/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:09:49 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/21 17:40:06 by mcombeau         ###   ########.fr       */
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
*	If there are multiple commands in a pipeline:
*		"The exit status of a pipeline is the exit status of the last command
*		in the pipeline"
*/
static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

/* prep_cmd_list:
*	Checks if the list of commands to execute is valid.
*	Returns true if it is, false if it is not.
*/
static bool	prep_cmd_list(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (cmd == NULL || cmd->command == NULL)
		return (false);
	while (cmd)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
	if (!create_pipes(data) || !check_infile_outfile(data))
		return (false);
	return (true);
}

/* create_children:
*	Creates a child process for each command to execute, except in the
*	case of a builtin command that is not piped, which executes in the
*	main process (no children created in this case).
*	Returns true when a process was created for each command or when a
*	builtin was executed alone.
*	Returns false if there was a fork error.
*/
static int	create_children(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	data->pid = -1;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

/* execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate.
*	Returns the exit code of the last child to terminate. Or
*	exit code 1 in case of failure in the child creation process.
*/
int	execute(t_data *data)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (!prep_cmd_list(data))
		return (EXIT_FAILURE);
	print_cmd_list(data);
	if (!data->cmd->pipe_output && !data->cmd->prev)
		{
			redirect_io(data->cmd->io_fds);
			ret = execute_builtin(data, data->cmd);
			restore_io(data->cmd->io_fds);
		}
		if (ret != CMD_NOT_FOUND)
			return (ret);
	return (create_children(data));
}
