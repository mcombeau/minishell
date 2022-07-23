#include "minishell.h"

/* errmsg:
*	Prints an error message to the standard error, prefixed with the
*	program name.
*	Returns with the specified error number.
*/
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

/* free_strs_array:
*	Frees an array of strings.
*/
void	free_str_array(char **strs)
{
	int i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}