/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   export.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:17:34 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:17:35 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cat_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->val)
		{
			ft_printf("%s=%s\n", tmp->key, tmp->val);
		}
		else
		{
			ft_printf("%s\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

void	parse_args(char *arg, char **key, char **val)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		*val = ft_strdup(equal + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*val = NULL;
	}
}

t_env	*check_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_or_update_env(t_data *data, char *arg)
{
	char	*key;
	char	*val;
	t_env	*existing;

	parse_args(arg, &key, &val);
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

int	export(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		cat_env(data->env);
		return (0);
	}
	while (args[i])
	{
		if (is_valid(args[i]) == 0)
		{
			ft_printf("wrong format\n");
			return (1);
		}
		add_or_update_env(data, args[i]);
		i++;
	}
	return (0);
}
