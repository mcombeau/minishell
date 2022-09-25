/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:30:41 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/25 16:28:55 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* get_key_value_pair:
*	Separates the given argument into a key-value pair
*	for the environment variable.
*	Returns an array of 2 strings containing the key and the
*	value of the new environment variable.
*	Returns NULL in case of error.
*/
static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof * tmp * (2 + 1));
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	tmp[0] = ft_calloc(i, sizeof * tmp);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		tmp[0][i] = arg[i];
		i++;
	}
	i++;
	j = 0;
	while (arg[i + j])
		j++;
	tmp[1] = ft_calloc(j, sizeof * tmp);
	j = 0;
	while (arg[i + j])
	{
		tmp[1][j] = arg[i + j]; 
		j++;
	}
	tmp[2] = NULL;
	return (tmp);
}

/* export_builtin:
*	Adds the given variables to the environment variables.
*	Returns 0 if all args were successfully added to env,
*	or 1 if one or more args were not added to env.
*/
int	export_builtin(t_data *data, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(data, tmp[0], tmp[1]);
			free(tmp);
		}
		i++;
	}
	return (ret);
}
