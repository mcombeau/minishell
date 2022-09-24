/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:07:03 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/24 15:09:08 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		free(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		lstclear_token(&data->token, &free);
	if (data && data->cmd)
		lst_clear_cmd(&data->cmd, &free);
	if (clear_history == true)
	{
		if (data && data->env)
			free_tab(data->env);
		rl_clear_history();
	}
}
