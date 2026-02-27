/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   env.c                                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:17:00 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:17:08 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->val)
		{
			ft_printf("%s", tmp->key);
			write(1, "=", 1);
			ft_printf("%s\n", tmp->val);
		}
		tmp = tmp->next;
	}
	return (0);
}
