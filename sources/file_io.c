#include "minishell.h"

bool	redirect_io(t_io_fds *io)
{
	io->stdin_backup = dup(STDIN_FILENO);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->fd_in != -1)
		dup2(io->fd_in, STDIN_FILENO);
	if (io->fd_out != -1)
		dup2(io->fd_out, STDOUT_FILENO);
	return (true);
}

bool	open_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if (io->infile)
	{
		if (io->mode == HEREDOC)
		{
			// Get heredoc contents and save them to a tmp file.
			// Open tmp file in read mode here.
			return (false); // change this return when heredoc is implemented
		}
		else
		{
			io->fd_in = open(io->infile, O_RDONLY, 644);
			if (io->fd_in == -1)
				return (errmsg("open", io->infile, strerror(errno), false));
		}
	}
	if (io->outfile)
	{
		if (io->mode == HEREDOC)
			io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 644);
		else
			io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 644);
		if (io->fd_out == -1)
			return (errmsg("open", io->outfile, strerror(errno), false));
	}
	return (redirect_io(io));
}

// Need functions to deal with heredoc
