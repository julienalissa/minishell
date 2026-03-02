/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execut_builtin.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:17:15 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:17:16 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execut_builtin(t_ast *node, t_data *data)
{
	if (!node || !node->args || !node->args[0])
		return (1);
	if (ft_strcmp(node->args[0], "echo") == 0)
		return (echo(node->args));
	else if (ft_strcmp(node->args[0], "cd") == 0)
		return (cd(node->args, data));
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(node->args[0], "export") == 0)
		return (export(node->args, data));
	else if (ft_strcmp(node->args[0], "unset") == 0)
		return (unset(node->args, data));
	else if (ft_strcmp(node->args[0], "env") == 0)
		return (env(data));
	else if (ft_strcmp(node->args[0], "exit") == 0)
		return (exit_42(node, data));
	else if (ft_strcmp(node->args[0], ":") == 0)
		return (0);
	else if (ft_strcmp(node->args[0], "!") == 0)
		return (1);
	return (1);
}
