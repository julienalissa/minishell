/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:17:34 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/16 17:49:29 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bbsort_it(int count, t_env **tab)
{
	t_env	*swap;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(tab[i]->key, tab[j]->key) > 0)
			{
				swap = tab[i];
				tab[i] = tab[j];
				tab[j] = swap;
			}
			j++;
		}
		i++;
	}
}

void	print_export_sorted(t_env *env)
{
	int		count;
	int		i;
	t_env	**tab;
	t_env	*tmp;

	i = 0;
	count = count_env(env);
	if (count <= 0)
		return ;
	tab = malloc(sizeof(t_env *) * count);
	if (!tab)
		return ;
	tmp = env;
	copy_it(tmp, tab);
	bbsort_it(count, tab);
	while (i < count)
	{
		ft_printf("declare -x %s", tab[i]->key);
		if (tab[i]->val)
			ft_printf("=\"%s\"", tab[i]->val);
		ft_printf("\n");
		i++;
	}
	free(tab);
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

int	make_home(char *home_val, char *val, char *key)
{
	char	*new_val;

	new_val = NULL;
	if (home_val)
	{
		if (val[1] == '\0')
			new_val = ft_strdup(home_val);
		else
			new_val = ft_strjoin(home_val, val + 1);
		free(val);
		val = new_val;
		if (!val)
		{
			free(key);
			return (1);
		}
	}
	return (0);
}
