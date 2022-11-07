/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:17:42 by mcombeau          #+#    #+#             */
/*   Updated: 2022/11/07 16:25:21 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmd_args(t_command *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		printf("\tArgs[%d] = %s\n", i, cmd->args[i]);
		i++;
	}
}

static void	print_cmd_io(t_command *cmd)
{
	if (!cmd->io_fds)
		return ;
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

void	print_cmd_list(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	printf("\n---- COMMAND LIST\n");
	while (cmd)
	{
		printf("--- Command = %s\n", cmd->command);
		print_cmd_args(cmd);
		printf("\tPipe_output = %d\n", cmd->pipe_output);
		print_cmd_io(cmd);
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

void	print_token_type(t_token *token, char *prefix)
{
	printf("%s", prefix);
	if (token->type == SPACES)
		printf("SPACES\n");
	else if (token->type == WORD)
		printf("WORD\n");
	else if (token->type == VAR)
		printf("VAR\n");
	else if (token->type == PIPE)
		printf("PIPE\n");
	else if (token->type == INPUT)
		printf("INPUT\n");
	else if (token->type == TRUNC)
		printf("TRUNC\n");
	else if (token->type == HEREDOC)
		printf("HEREDOC\n");
	else if (token->type == APPEND)
		printf("APPEND\n");
	else if (token->type == END)
		printf("END\n");
}

void	print_token_list(t_token **tokens)
{
	t_token	*lst;
	int		i;

	lst = *tokens;
	printf("\n---- TOKEN LIST\n");
	i = 0;
	while (lst)
	{
		printf("--- Token [%d] [%p]\n", i, lst);
		printf("\tString = [%s]\n", lst->str);
		printf("\tStr backup = [%s]\n", lst->str_backup);
		print_token_type(lst, "\tType = ");
		printf("\tStatus = %d\n", lst->status);
		if (lst->prev)
			printf("\tPrev = [%p]\n", lst->prev);
		else
			printf("\tPrev = NULL\n");
		if (lst->next)
			printf("\tNext = [%p]\n", lst->next);
		else
			printf("\tNext = NULL\n");
		i++;
		lst = lst->next;
	}
}
