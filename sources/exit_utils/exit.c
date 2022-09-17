/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:06:38 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/17 19:06:40 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* exit_shell:
*	Cleanly exits the minishell program by closing all opened
*	fds and freeing all allocated memory.
*/
void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exno);
}
