/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:18:42 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/13 18:36:22 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	creat_env(t_data *data)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*env_tmp;

	// if (!data->envp || !data->envp[0])
	// {
	// 	no_env(data);
	// 	return ;
	// }
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
	while(temp)
	{
		res[i] = ft_strjoin(temp->key, "=");
		res[i] = ft_strjoin_free_s1(res[i], temp->val);
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return(res);
}

int	lstsize_env(t_env *env)
{
	int		i;
	t_env	*temp;

	temp = env;
	i = 0;
	while(temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

// void	no_env(t_data *data)
// {
// 	(void);
// 	// Fonction pour mettre les 3 variables denvironnement si il ny a pas de env au lancement
// }
