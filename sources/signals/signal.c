/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:06:43 by mcombeau          #+#    #+#             */
/*   Updated: 2022/10/06 15:01:21 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* signal_reset_prompt:
*	Resets the readline user input prompt for interactive signal handling.
*/
void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* set_interactive_signal_trap:
*	Sets a signal trap to intercept SIGINT (ctrl-c). SIGINT resets
*	the user input prompt to a new blank line.
*	Used when minishell is in interactive mode, meaning it is awaiting
*	user input.
*/
void	set_interactive_signal_trap(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/* signal_print_newline:
*	Prints a newline for noninteractive signal handling.
*/
void	signal_print_newline(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

/* set_noninteractive_signal_trap:
*	Sets a signal trap to intercept SIGINT (ctrl -c) and SIGQUIT (ctrl -D).
*	Used when minishell is in noninteractive mode, meaning it is not awaiting
*	user input. For example, when a command is running (i.e. cat), minishell
*	should not react to SIGINT and SIGQUIT because only the running process (cat)
*	needs to react to those signals.
*/
void	set_noninteractive_signal_trap(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

/* ignore_sigquit:
*	Replaces SIGQUIT signals (ctrl-\) with SIG_IGN to ignore
*	the signal.
*/
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
