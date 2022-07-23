#include "minishell.h"

int	errmsg(char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = false;
	msg = ft_strjoin("minishell: ", command);
	msg = ft_strjoin(msg, ": ");
	if (detail != NULL)
	{
		if (ft_strncmp(command, "export", 7) == 0
			|| ft_strncmp(command, "unset", 6) == 0)
			detail_quotes = true;
		if (detail_quotes)
			msg = ft_strjoin(msg, "`");
		msg = ft_strjoin(msg, detail);
		if (detail_quotes)
			msg = ft_strjoin(msg, "`");
		msg = ft_strjoin(msg, ": ");
	}
	msg = ft_strjoin(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (error_nb);
}