#include "../../include/minishell.h"

static char	*ft_strjoin_path(char const *s1, char const *s2);

void	wait_all_process(t_data *data)
{
	int	status;

	status = 0;
	while ((waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
			data->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->last_exit_code = 128 + WTERMSIG(status);
	}
}

int	wait_process(t_data *data)
{
	int	status;
	int	ret_status;

	status = 0;
	ret_status = 0;
	waitpid(data->exec->pids[data->exec->nb_cmds - 1], &status, 0);
	if (WIFEXITED(status))
		ret_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret_status = 128 + WTERMSIG(status);
	return (ret_status);
}

void	dup_and_close(int std_target, int fd)
{
	if (std_target == fd)
		return ;
	if (dup2(fd, std_target) < 0)
		ft_error("Error: dup2 failed\n");
	close(fd);
}

char	*find_path(t_ast *node, t_data *data)
{
	int		i;
	char	*ret;
	t_env	*temp;
	char	**path;

	i = 0;
	if (ft_strchr(node->args[0], '/'))
	{
		if (access(node->args[0], F_OK | X_OK) == 0)
			return (ft_strdup(node->args[0]));
		return (NULL);
	}
	temp = data->env;
	i = 0;
	while ((ft_strncmp(temp->key, "PATH", ft_strlen("PATH"))) != 0)
		temp = temp->next;
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
