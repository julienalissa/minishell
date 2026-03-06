/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 07:10:18 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/06 07:10:19 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_error_code(char *res, t_data *data);
static char	*ft_strjoin_free_s1(char *s1, char *s2);
static char	*result_expand(t_env *env_temp, char *name, t_data *data);
static char	*expand_key(t_env *env_temp, char *name, char *res, int *i);

void	expand_dollar(char *name, t_list **lst, t_data *data)
{
	char	*res;
	t_env	*env_temp;

	env_temp = data->env;
	res = result_expand(env_temp, name, data);
	(*lst)->content = ft_strdup(res);
	free(res);
}

static char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

static char	*result_expand(t_env *env_temp, char *name, t_data *data)
{
	char	temp_char[2];
	char	*result;
	int		i;

	i = 0;
	temp_char[1] = '\0';
	result = ft_strdup("");
	while (name[i])
	{
		if (name[i] != '$' || (!ft_isalnum(name[i + 1]) && name[i + 1] != '_'
				&& name[i + 1] != '?'))
		{
			temp_char[0] = name[i++];
			result = ft_strjoin_free_s1(result, temp_char);
		}
		else if (name[++i] == '?')
		{
			result = expand_error_code(result, data);
			i++;
		}
		else
			result = expand_key(env_temp, name, result, &i);
	}
	return (result);
}

static char	*expand_error_code(char *res, t_data *data)
{
	char	*temp;
	char	*new_res;

	temp = ft_itoa(data->last_exit_code);
	new_res = ft_strjoin_free_s1(res, temp);
	free(temp);
	return (new_res);
}

static char	*expand_key(t_env *env_temp, char *name, char *res, int *i)
{
	int		start;
	int		len;
	char	*new_res;
	char	*temp;

	start = *i;
	new_res = NULL;
	while (name[*i] && (ft_isalnum(name[*i]) || name[*i] == '_'))
		(*i)++;
	temp = ft_substr(name, start, *i - start);
	len = ft_strlen(temp);
	while (env_temp)
	{
		if (!ft_strncmp(env_temp->key, temp, len)
			&& (int)ft_strlen(env_temp->key) == len)
			new_res = ft_strjoin_free_s1(res, env_temp->val);
		env_temp = env_temp->next;
	}
	if (!new_res)
	{
		new_res = ft_strdup(res);
		free(res);
	}
	free(temp);
	return (new_res);
}
