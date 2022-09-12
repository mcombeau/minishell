/* _XOPEN_SOURCE definition is necessary for sigaction. Without it,
*	"incomplete type" errors appear during compilation.*/
# define _XOPEN_SOURCE
# include "minishell.h"

/* signal_reset_prompt:
*	Resets the readline user input prompt for signal handling.
*/
void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* set_signal_trap:
*	Sets a signal trap to intercept SIGINT (ctrl-c). SIGINT resets
*	the user input prompt to a new blank line.
*/
void	set_signal_trap(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/* ignore_sigquit:
*	Replaces SIGQUIT signals (ctrl-\) with SIG_IGN to ignore
*	the signal.
*/
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}