/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:20:13 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/10 16:43:21 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*if_backslash(t_ast *node);
static char	*ft_strjoin_path(char const *s1, char const *s2);

char	*find_path(t_ast *node, t_data *data)
{
	int		i;
	char	*ret;
	t_env	*temp;
	char	**path;

	i = 0;
	if (ft_strchr(node->args[0], '/') && node->args[0][0] != '.')
		return (if_backslash(node));
	temp = data->env;
	while (temp && ft_strncmp(temp->key, "PATH", ft_strlen("PATH")) != 0)
		temp = temp->next;
	if (!temp || !temp->val || temp->val[0] == '\0')
		return (ft_strdup(node->args[0]));
	path = ft_split(temp->val, ':');
	while (path[i])
	{
		ret = ft_strjoin_path(path[i], node->args[0]);
		if (access(ret, F_OK | X_OK) == 0)
			return (ft_split_clear(path), ret);
		else
			free(ret);
		i++;
	}
	ft_split_clear(path);
	return (NULL);
}

static char	*if_backslash(t_ast *node)
{
	if (access(node->args[0], X_OK) == 0)
		return (ft_strdup(node->args[0]));
	else
		return (NULL);
}

static char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	newstr = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, len1 + 1);
	if (newstr[len1 - 1] != '/')
	{
		newstr[len1++] = '/';
		newstr[len1 + 1] = '\0';
	}
	ft_strlcpy(newstr + len1, s2, (len2 + 1));
	return (newstr);
}
