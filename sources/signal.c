# include "minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		print_prompt();
	}
}