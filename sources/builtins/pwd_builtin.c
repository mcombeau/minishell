/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:30:28 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/17 18:30:34 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* pwd_builtin:
*	Executes the builtin pwd command and displays the
*	current working directory path.
*	Returns 0 if successful, 1 if an error occured.
*/
int	pwd_builtin(t_data *data, char **args)
{
	char	buf[BUFSIZ];
	char	*cwd;

	(void)args;
	(void)data;
	cwd = getcwd(buf, BUFSIZ);
	if (!cwd)
	{
		errmsg_cmd("pwd", NULL, strerror(errno), errno);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
