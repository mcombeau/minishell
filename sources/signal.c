# include "minishell.h"

/* handle_signal:
*	Intercepts interrupt and quit signals coming from
*	ctrl-c and ctrl-\, which only print a new line,
*	reset the signal traps and display the prompt again.
*/
void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		signal(SIGINT, handle_signal);
	}
	if (signo == SIGQUIT){
		signal(SIGQUIT, handle_signal);
	}
}