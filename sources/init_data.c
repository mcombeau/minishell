#include "minishell.h"

/* init_env:
*	Initializes a data variable with the contents of the environment
*	variables inherited from the original shell.
*	Returns 0 on failure, 1 on success.
*/
static bool	init_env(t_data *data, char **env)
{
	int		i;
	char	buff[BUFSIZ];

	data->env = ft_calloc(env_var_count(env) + 1, sizeof * data->env);
	if (!env || !env[0])
	{
		errmsg_cmd("Warning", NULL,
			"No environment. Please provide paths for commands.", 1);
		set_env_var(data, "PWD", getcwd(buff, BUFSIZ));
	}
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (false);
		i++;
	}
	return (true);
}

// TODO: Fix env init for var expansion + export unset to work!
bool	init_data(t_data *data, char **env)
{
	if (!init_env(data, env))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
//	data->env = env;
	data->token = NULL;
	return (true);
}

// TODO: exit validation
void	init_io(t_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->mode = 0;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}