/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:03:12 by mcombeau          #+#    #+#             */
/*   Updated: 2022/07/20 13:13:01 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

/******************************************************************************
*								MACROS										  *
******************************************************************************/

# define PROMPT "\033[0;35m➜\033[0;m \033[0;33mMinishell >\033[0;m"

/******************************************************************************
*							GLOBAL VARIABLES								  *
******************************************************************************/
char	**g_env_vars;

/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/

// exit.c
void	exit_shell(void);

// env.c
bool	init_env(char **env);
void	sh_builtin_env(void);
int		get_env_var_index(char *var);

// pwd.c
void	sh_builtin_pwd(void);

// echo.c
bool	sh_builtin_echo(char **args);

// signal.c
void	handle_signal(int signo);

// test.c
void	test_env(int ac, char **av, char **env);

#endif