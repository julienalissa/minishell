/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:16:41 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/17 15:04:52 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*my_getenv(char *my_home, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, my_home) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

int	check_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("-bash: cd: too many arguments", 2);
		return (-1);
	}
	return (0);
}

void	change_old_and_pwd(char *path_buf, t_data *data, char *cwd_buf)
{
	char	*tmp;

	tmp = NULL;
	if (path_buf[0] != '\0')
	{
		tmp = ft_strjoin("OLDPWD=", path_buf);
		if (tmp)
		{
			add_or_update_env(data, tmp);
			free(tmp);
		}
	}
	if (getcwd(cwd_buf, sizeof(cwd_buf)))
	{
		tmp = ft_strjoin("PWD=", cwd_buf);
		if (tmp)
		{
			add_or_update_env(data, tmp);
			free(tmp);
		}
	}
}

void	check_home(t_data *data, char **args, char **path)
{
	char	*home;

	home = my_getenv("HOME", data->env);
	if (!args[1] || ft_strcmp(args[1], "~") == 0 || args[1][1] == '\0')
		(*path) = home;
	else
		(*path) = ft_strjoin(home, args[1] + 1);
}

int	cd(char **args, t_data *data)
{
	char	path_buf[1024];
	char	cwd_buf[1024];
	char	*path;
	int		ret;

	path = NULL;
	if (check_args(args) == -1)
		return (1);
	if (!getcwd(path_buf, sizeof(path_buf)))
		path_buf[0] = '\0';
	if (!args[1] || ft_strcmp(args[1], "~") == 0 || (args[1][0] == '~'
		&& (args[1][1] == '/' || args[1][1] == '\0')))
		check_home(data, args, &path);
	else
		path = args[1];
	ret = chdir(path);
	if (error_ret(args, path, ret) == 1)
		return (1);
	change_old_and_pwd(path_buf, data, cwd_buf);
	if (args[1] && args[1][0] == '~' && args[1][1] == '/')
		free(path);
	return (0);
}
