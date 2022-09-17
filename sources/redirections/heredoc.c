#include "minishell.h"

// TODO if contains var, make mini expander
bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int		tmp_fd;
	char	*line;

	(void)data;
	line = NULL;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			return (false);
		if (ft_strcmp(line, io->heredoc_delimiter) == 0)
			break;
		if (ft_strchr(line, '$'))
			printf("Heredoc line contains variable.\n");
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
	return (true);
}
