/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:52:31 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/20 15:28:02 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			free(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free(tmp);
		}
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

/* fill_heredoc:
*	Copies user input into a temporary file. If user inputs an environment variable
*	like $USER, expands the variable before writing to the heredoc.
*	Returns true on success, false on failure.
*/
bool	fill_heredoc(t_data *data, char *delimiter, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(">");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
			return (true);
		if (ft_strchr(line, '$'))
		{
			line = get_expanded_var_line(data, line);
			if (!line)
			{
				free(line);
				return (false);
			}
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
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
