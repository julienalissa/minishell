/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:17:34 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/16 18:08:28 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_existing(t_data *data, char *key, char *val)
{
	t_env	*existing;

	existing = check_env(data->env, key);
	if (existing)
	{
		free(existing->val);
		existing->val = val;
		free(key);
	}
	else
		lstadd_back_env(&data->env, lstnew_env(key, val));
}

void	add_or_update_env(t_data *data, char *arg)
{
	char	*key;
	char	*val;
	t_env	*tmp_env;
	char	*home_val;

	parse_args(arg, &key, &val);
	if (val && val[0] == '~')
	{
		home_val = NULL;
		tmp_env = data->env;
		while (tmp_env)
		{
			if (ft_strcmp(tmp_env->key, "HOME") == 0)
			{
				home_val = tmp_env->val;
				break ;
			}
			tmp_env = tmp_env->next;
		}
		if (make_home(home_val, val, key) == 1)
			return ;
	}
	ft_existing(data, key, val);
}

int	check_valid(char *arg, t_data *data, int *i, int *j)
{
	if (is_valid(arg) == 0)
	{
		ft_printf("wrong format\n");
		free(arg);
		return (1);
	}
	add_or_update_env(data, arg);
	free(arg);
	*i = *j;
	return (0);
}

int	ft_make_it(int *j, int *i, char **arg, char **args)
{
	char	*tmp;
	int		has_equal;

	*j = *i;
	(*arg) = ft_strdup(args[*j]);
	if (!(*arg))
		return (1);
	has_equal = (ft_strchr((*arg), '=') != NULL);
	*j = *j + 1;
	while (args[*j])
	{
		if (!has_equal)
			return (2);
		if (ft_strchr(args[*j], '='))
			return (2);
		tmp = ft_strjoin((*arg), args[*j]);
		free(*arg);
		if (!tmp)
			return (1);
		(*arg) = tmp;
		*j = *j + 1;
	}
	return (0);
}

int	export(char **args, t_data *data)
{
	int		i;
	int		j;
	char	*arg;

	i = 1;
	arg = NULL;
	if (!args[1])
	{
		print_export_sorted(data->env);
		return (0);
	}
	while (args[i])
	{
		if (ft_make_it(&j, &i, &arg, args) == 2)
			break ;
		if (ft_make_it(&j, &i, &arg, args) == 1)
			return (1);
		if (check_valid(arg, data, &i, &j) == 1)
			return (1);
	}
	return (0);
}
