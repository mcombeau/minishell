#include "minishell.h"

int	errmsg(char *command, char *detail, char *error_message, int errno)
{
	if (detail != NULL)
		printf("minishell: %s: %s: %s\n", command, detail, error_message);
	else
		printf("minishell: %s: %s\n", command, error_message);
	return (errno);
}