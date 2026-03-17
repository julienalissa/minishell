/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   envp_utils.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:18:46 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:18:47 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*define_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	if (!key)
		return (NULL);
	return (key);
}

char	*define_value(char *env)
{
	unsigned int	start;
	char			*value;
	int				i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	start = i + 1;
	value = ft_strdup(env + start);
	if (!value)
		return (NULL);
	return (value);
}

char	*create_env_str(t_env *env)
{
	char	*env_str;
	char	*full_str;

	if (env->val)
	{
		env_str = ft_strjoin(env->key, "=");
		if (!env_str)
			return (NULL);
		full_str = ft_strjoin(env_str, env->val);
		free(env_str);
		if (!full_str)
			return (NULL);
		return (full_str);
	}
	else
		return (ft_strdup(env->key));
}

int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**alloc_envp(t_env *env, int count)
{
	int		i;
	t_env	*tmp;
	char	**new_envp;

	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		new_envp[i] = create_env_str(tmp);
		if (!new_envp[i])
		{
			free(new_envp);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
