#include "minishell.h"

/* make_str_from_tab:
*	Creates a single string from an array of strings by
*	joining a string to the next.
*	Returns the string.
*/
static char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free_ptr(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free_ptr(tmp);
		}
	}
	free_str_tab(tab);
	return (str);
}

/* get_exoanded_var_line:
*	Prepares a line containing '$' for environment variable expansion.
*	Splits the line into words to avoid issues with inexistent
*	environment variables.
*	ex. $USER uses $LANGUAGE -> username uses en_US:en
*	Returns a new line with expanded variables.
*/
static char	*get_expanded_var_line(t_data *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = var_expander_heredoc(data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

static bool	delim_between_quotes(char *delim)
{
	int	len;
	
	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
		return (true);
//	printf("Delim not between quotes. [0]=[%c], [%d]=[%c]\n", delim[0], len, delim[len]);
	return (false);
}

/* fill_heredoc:
*	Copies user input into a temporary file. If user inputs an environment variable
*	like $USER, expands the variable before writing to the heredoc.
*	Returns true on success, false on failure.
*/
bool	fill_heredoc(t_data *data, char *delimiter, int fd)
{
	char	*line;
	char	*quoteless_delim;

	quoteless_delim = ft_strtrim(delimiter, "\'\"");
	line = NULL;
	while (1)
	{
		ignore_sigquit();
		set_interactive_signal_trap();
		line = readline(">");
		set_noninteractive_signal_trap();
		if (line == NULL || ft_strcmp(line, quoteless_delim) == 0)
			return (errmsg_cmd("warning", "here-document delimited by end-of-file: wanted", quoteless_delim, true));
		if (!delim_between_quotes(delimiter) && ft_strchr(line, '$'))
		{
			line = get_expanded_var_line(data, line);
			if (!line)
			{
				free_ptr(line);
				return (false);
			}
		}
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(quoteless_delim);
	return (false);
}

/* get_heredoc:
*	Opens a heredoc awaiting user input.
*	Translates any given variables into	their environment values.
*	Returns false in case of error, true if successful.
*/
bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(data, io->heredoc_delimiter, tmp_fd);
	close(tmp_fd);
	return (ret);
}

static char	*get_heredoc_name(void)
{
	char		*name;
	static int	i;

	name = ft_strjoin(HEREDOC_NAME, ft_itoa(i));
	i++;
	return (name);
}

//TODO: if quotes surround delimiter, do not expand variables.
void	parse_heredoc(t_data *data, t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;
	t_io_fds	*io;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	io = cmd->io_fds;
	if (io->infile)
	{
		if (io->fd_in == -1)
			return ;
		if (io->heredoc_delimiter != NULL)
		{
			free_ptr(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->infile);
		}
		free_ptr(io->infile);
		close(io->fd_in);
	}
	io->infile = get_heredoc_name();
//	printf("New heredoc name is %s\n", io->infile);
	io->heredoc_delimiter = ft_strdup(temp->next->str);
//	printf("delimiter = [%s]\n", io->heredoc_delimiter);
	if (get_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
