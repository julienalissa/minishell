/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:20:13 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/18 07:08:00 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_strjoin_path(char const *s1, char const *s2);

char	*find_path(t_ast *node, t_data *data)
{
	int		i;
	char	*ret;
	t_env	*temp;
	char	**path;

	i = 0;
	if (ft_strchr(node->args[0], '/'))
		return (ft_strdup(node->args[0]));
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
			return (ft_freetab(path), ret);
		else
			free(ret);
		i++;
	}
	ft_freetab(path);
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

void	path_not_found(t_data *data, t_ast *node, char *path)
{
	int	if_exist;

	if (ft_strchr(node->args[0], '/'))
	{
		if_exist = access(node->args[0], F_OK);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": ", 2);
		free_child(data, path);
		if (access(node->args[0], X_OK) < 0 && if_exist == 0)
		{
			ft_putendl_fd("Permission denied", 2);
			exit (126);
		}
		perror("");
		free_child(data, path);
		exit (127);
	}
	ft_putstr_fd(node->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_child(data, path);
	exit (127);
}

int	get_status_hd(t_data *data, t_redir *redir, int *fdpipe, int status)
{
	int	ret_status;

	ret_status = 0;
	if (WIFEXITED(status))
		ret_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret_status = 128 + WTERMSIG(status);
	signals();
	if (ret_status == 130 || ret_status == 131)
	{
		write(1, "\n", 1);
		data->last_exit_code = ret_status;
		return (-1);
	}
	else
	{
		redir->fd_hd = fdpipe[0];
		if (redir->fd_hd < 0)
			return (-1);
	}
	return (1);
}
