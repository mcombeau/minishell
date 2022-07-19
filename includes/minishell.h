/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:03:12 by mcombeau          #+#    #+#             */
/*   Updated: 2022/07/19 12:49:12 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include "libft.h"

char	**g_env_vars;

/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/

// exit.c
void	exit_shell(void);

// env.c
bool	init_env(char **env);

// test.c
void	test_env(int ac, char **av, char **env);

#endif