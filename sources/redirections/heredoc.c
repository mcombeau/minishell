#include "minishell.h"

void	get_heredoc(t_io_fds *io)
{
	int		tmp_fd;
	char	*line;

	line = NULL;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, io->heredoc_delimiter) == 0)
			break;
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
}
