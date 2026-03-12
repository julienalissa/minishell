/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:16:51 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/09 16:30:15 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_it(char **args, int *i)
{
	int	j;

	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
	{
		j = 2;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != '\0')
			break ;
		(*i)++;
	}
	if (*i > 1)
		return (1);
	return (0);
}

int	echo(char **args, t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!args)
		return (1);
	if (args[1] && args[1][0] == '~' && args[1][1] == '\0')
	{
		i = 0;
		while (data->env)
		{
			if (ft_strncmp(data->env->key, "HOME", 4) == 0)
			{
				ft_printf("%s\n", data->env->val);
				return (0);
			}
			data->env = data->env->next;
		}
	}
	if (check_it(args, &i))
		newline = 0;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
