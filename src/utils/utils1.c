#include "../../include/minishell.h"

void	set_data(t_data *data, char **env)
{
	ft_bzero(data, sizeof(t_data));
	data->envp = env;
}

void	ft_error(char *errorname)
{
	perror(errorname);
	exit (EXIT_FAILURE);
}

