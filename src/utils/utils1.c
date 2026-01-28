#include "../../include/minishell.h"

void	set_data(t_data *data, char **env, t_ast *node, t_exec *exec)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(node, sizeof(t_ast));
	ft_bzero(exec, sizeof(t_exec));
	data->envp = env;
}

void	ft_error(char *errorname)
{
	perror(errorname);
	exit (EXIT_FAILURE);
}

