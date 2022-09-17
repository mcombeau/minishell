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

	str = NULL;
	i = 0;
	while (tab[i])
	{
		if (i == 0)
			str = ft_strdup(tab[i]);
		else
		{
			tmp = str;
			str = ft_strjoin(tmp, tab[i]);
			free(tmp);
		}
		if (!str)
			break ;
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free(tmp);
		}
		i++;
	}
	free_tab(tab);
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

/* get_heredoc:
*	Opens a heredoc awaiting user input.
*	Translates any given variables into	their environment values.
*	Returns false in case of error, true if successful.
*/
bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int		tmp_fd;
	char	*line;
	bool	ret;
	
	ret = true;
	line = NULL;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, io->heredoc_delimiter) == 0)
			break ;
		if (ft_strchr(line, '$'))
		{
			line = get_expanded_var_line(data, line);
			if (!line)
			{
				ret = false;
				free(line);
				break ;
			}
		}
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
	return (ret);
}
