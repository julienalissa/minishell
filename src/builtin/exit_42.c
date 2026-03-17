/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_42.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:17:24 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/09 15:43:21 by lucasdebarn      ###   ########.fr       */
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
	data->save_status = status;
	data->need_exit = 1;
	return (status);
}
