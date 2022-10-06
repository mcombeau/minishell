#include "minishell.h"

void	free_str(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}