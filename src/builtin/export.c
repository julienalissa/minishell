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

static void	print_export_sorted(t_env *env)
{
	int		count;
	int		i;
	int		j;
	t_env	**strr;
	t_env	*tmp;
	t_env	*swap;

	count = count_env(env);
	if (count <= 0)
		return;
	strr = malloc(sizeof(t_env *) * count);
	if (!strr)
		return;
	tmp = env;
	i = 0;
	while (tmp)
	{
		strr[i++] = tmp;
		tmp = tmp->next;
	}
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(strr[i]->key, strr[j]->key) > 0)
			{
				swap = strr[i];
				strr[i] = strr[j];
				strr[j] = swap;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		ft_printf("declare -x %s", strr[i]->key);
		if (strr[i]->val)
			ft_printf("=\"%s\"", strr[i]->val);
		ft_printf("\n");
		i++;
	}
	free(strr);
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
	t_env	*tmp_env;

	parse_args(arg, &key, &val);
	if (val && val[0] == '~')
	{
		char	*home_val;
		char	*new_val;

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
				return;
			}
		}
	}
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
	int		i;
	int		j;
	char	*arg;
	char	*tmp;
	int		has_equal;

	i = 1;
	if (!args[1])
	{
		print_export_sorted(data->env);
		return (0);
	}
	while (args[i])
	{
		j = i;
		arg = ft_strdup(args[j]);
		if (!arg)
			return (1);
		has_equal = (ft_strchr(arg, '=') != NULL);
		j++;
		while (args[j])
		{
			if (!has_equal)
				break ;
			if (ft_strchr(args[j], '='))
				break ;
			tmp = ft_strjoin(arg, args[j]);
			free(arg);
			if (!tmp)
				return (1);
			arg = tmp;
			j++;
		}
		if (is_valid(arg) == 0)
		{
			ft_printf("wrong format\n");
			free(arg);
			return (1);
		}
		add_or_update_env(data, arg);
		free(arg);
		i = j;
	}
	return (0);
}
