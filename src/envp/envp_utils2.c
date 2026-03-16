/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:08:25 by ludebarn          #+#    #+#             */
/*   Updated: 2026/03/16 15:11:41 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	get_shlvl(t_data *data, t_env **tmp);

void	add_shlvl(t_data *data)
{
	t_env	*tmp;
	int		lvl;

	tmp = data->env;
	while (tmp && ft_strcmp(tmp->key, "SHLVL") != 0)
		tmp = tmp->next;
	if (!tmp)
		get_shlvl(data, &tmp);
	lvl = 0;
	if (tmp->val)
		lvl = ft_atoi(tmp->val);
	lvl++;
	free(tmp->val);
	tmp->val = ft_itoa(lvl);
	if (!tmp->val)
		return ;
}

static void	get_shlvl(t_data *data, t_env **tmp)
{
	char	*new_val;

	new_val = ft_strdup("1");
	if (!new_val)
		return ;
	(*tmp) = lstnew_env(ft_strdup("SHLVL"), new_val);
	if (!(*tmp))
		return ;
	lstadd_back_env(&data->env, (*tmp));
	return ;
}
