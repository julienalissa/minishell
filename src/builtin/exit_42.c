#include "../../include/minishell.h"

int	exit_42(t_ast *node, t_data *data)
{
	int status;

	status = 0;
	ft_printf("exit\n");
	if (node->args[1])
		status = ft_atoi(node->args[1]);
	lstclear_token(&data->token);
	free_node(node);
	lstclear_env(data);
	if (data->exec->pids)
		free(data->exec->pids);
	free(data->exec);
	exit(status);
}
