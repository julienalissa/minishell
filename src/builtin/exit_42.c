/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   exit_42.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:17:24 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:17:25 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_42(t_ast *node, t_data *data)
{
	int	status;

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
