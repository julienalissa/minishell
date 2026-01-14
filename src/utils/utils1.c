#include "../../include/minishell.h"

void ft_error(char *errorname)
{
	ft_putstr_fd(errorname, 2);
	exit(EXIT_FAILURE);
}

void	set_data(t_data *data, char **env)
{
	ft_bzero(data, sizeof(data));
	data->envp = env;
	data->flag_states = NORMAL;
}

