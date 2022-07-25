#include "minishell.h"

// TODO : heredoc functions.

/* restore_io:
*	Restores the original standard input and standard output
*	to their original fds of 0 and 1. Used to clear the input/output
*	fds after execution, in preparation for the next set of user commands.
*	Returns 1 if the duplication was successful, 0 if not.
*/
bool	restore_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (io->stdin_backup != -1)
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = errmsg("dup2", "restoring stdin", strerror(errno), false);
	if (io->stdout_backup != -1)
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = errmsg("dup2", "restoring stdout", strerror(errno), false);
	return (ret);
}

/* redirect_io:
*	Duplicates the input and output fds to the standard input and output.
*	Backs up the standard input and output before replacing them in order
*	to restore them after execution.
*	Returns 1 for success, 0 in case of error.
*/
static bool	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ret = errmsg("dup", "stdin backup", strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ret = errmsg("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = errmsg("dup2", io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg("dup2", io->outfile, strerror(errno), false);
	return (ret);
}

/* bool_open_infile:
*	Opens the specified input file in read-only mode. If the input is a
*	heredoc, creates a temporary file to write the contents and uses
*	that temporary file as input.
*	Returns 1 on success, 0 on failure.
*/
static bool	open_infile(t_io_fds *io)
{
	if (!io->infile)
		return (true);
	if (io->mode == HEREDOC)
	{
		// Get heredoc contents and save them to a tmp file.
		// Open tmp file in read mode here.
		return (false); // change this return when heredoc is implemented
	}
	else
	{
		io->fd_in = open(io->infile, O_RDONLY);
		if (io->fd_in == -1)
			return (errmsg("open", io->infile, strerror(errno), false));
	}
	return (true);
}

/* open_outfile:
*	Opens the provided output file in write-only mode. If the specified mode
*	is HEREDOC or APPEND, opens the file in append mode, otherwise opens in
*	truncate mode.
*	Returns 1 on success, 0 on failure.
*/
static bool	open_outfile(t_io_fds *io)
{
	if (!io->outfile)
		return (true);
	if (io->mode == HEREDOC || io->mode == APPEND)
		io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (io->fd_out == -1)
		return (errmsg("open", io->outfile, strerror(errno), false));
	return (true);
}

/* open_infile_outfile:
*	Opens the input and output files and redirects the input and output
*	accordingly.
*	Returns 1 on success, 0 on failure.
*/
bool	open_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if (open_infile(io) == true && open_outfile(io) == true)
		return (redirect_io(io));
	return (false);
}

