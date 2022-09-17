/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:07:03 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/17 19:07:14 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
