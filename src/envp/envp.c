/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:18:42 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/16 15:12:03 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	creat_env(t_data *data)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*env_tmp;

	if (!data->envp || !data->envp[0])
	{
		no_env(data);
		return ;
	}
	i = 0;
	while (data->envp[i])
	{
		key = define_key(data->envp[i]);
		value = define_value(data->envp[i]);
		env_tmp = lstnew_env(key, value);
		if (!env_tmp)
		{
			free(value);
			free(key);
			lstclear_env(data);
		}
		lstadd_back_env(&data->env, env_tmp);
		i++;
	}
}

char	**get_current_env(t_data *data)
{
	char	**res;
	t_env	*temp;
	int		size;
	int		i;

	i = 0;
	temp = data->env;
	size = lstsize_env(data->env);
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	while (temp)
	{
		res[i] = ft_strjoin(temp->key, "=");
		res[i] = ft_strjoin_free_s1(res[i], temp->val);
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

int	lstsize_env(t_env *env)
{
	int		i;
	t_env	*temp;

	temp = env;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	no_env(t_data *data)
{
	char	*pwd;
	t_env	*env_tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	env_tmp = lstnew_env(ft_strdup("PWD"), ft_strdup(pwd));
	if (!env_tmp)
	{
		free(pwd);
		return ;
	}
	lstadd_back_env(&data->env, env_tmp);
	env_tmp = lstnew_env(ft_strdup("OLDPWD"), ft_strdup(""));
	if (!env_tmp)
		return (free(pwd));
	lstadd_back_env(&data->env, env_tmp);
	env_tmp = lstnew_env(ft_strdup("SHLVL"), ft_strdup("0"));
	if (!env_tmp)
		return (free(pwd));
	lstadd_back_env(&data->env, env_tmp);
	free(pwd);
}
