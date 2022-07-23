#include "minishell.h"

int	errmsg(char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;

	msg = ft_strjoin("minishell: ", command);
	msg = ft_strjoin(msg, ": ");
	if (detail != NULL)
	{
		msg = ft_strjoin(msg, "`");
		msg = ft_strjoin(msg, detail);
		msg = ft_strjoin(msg, "`: ");
	}
	msg = ft_strjoin(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (error_nb);
}