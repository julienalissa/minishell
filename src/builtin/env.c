/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   env.c                                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/03/05 20:53:48 by jualissa       #+#    #+#                */
/*   Updated: 2026/03/05 20:53:55 by jualissa       ########   odam.nl        */
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
