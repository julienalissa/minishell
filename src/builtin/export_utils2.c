/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:36:48 by ludebarn          #+#    #+#             */
/*   Updated: 2026/03/16 17:55:52 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_ret(char **args, char *path, int ret)
{
	if (ret != 0)
	{
		perror("cd");
		if (args[1] && args[1][0] == '~' && args[1][1] == '/')
			free(path);
		return (1);
	}
	return (0);
}

int	is_valid(char *s)
{
	int	i;

	i = 1;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	copy_it(t_env *tmp, t_env **tab)
{
	int	i;

	i = 0;
	while (tmp)
	{
		tab[i] = tmp;
		i = i + 1;
		tmp = tmp->next;
	}
}
