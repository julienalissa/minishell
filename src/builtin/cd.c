/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   cd.c                                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:16:41 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:16:42 by jualissa       ########   odam.nl        */
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

int	cd(char **args, t_data *data)
{
	char	path_buf[1024];
	char	cwd_buf[1024];
	char	*path;
	char	*home;
	int		ret;
	char	*tmp;
	int		argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc > 2)
	{
		ft_putendl_fd("-bash: cd: too many arguments", 2);
		return (1);
	}
	if (!getcwd(path_buf, sizeof(path_buf)))
		path_buf[0] = '\0';
	if (!args[1] || ft_strcmp(args[1], "~") == 0 || (args[1][0] == '~'
			&& (args[1][1] == '/' || args[1][1] == '\0')))
	{
		home = my_getenv("HOME", data->env);
		if (!home)
		{
			return (0);
		}
		if (!args[1] || ft_strcmp(args[1], "~") == 0 || args[1][1] == '\0')
			path = home;
		else
			path = ft_strjoin(home, args[1] + 1);
	}
	else
		path = args[1];
	ret = chdir(path);
	if (ret != 0)
	{
		perror("cd");
		if (args[1] && args[1][0] == '~' && args[1][1] == '/')
			free(path);
		return (1);
	}
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
	if (args[1] && args[1][0] == '~' && args[1][1] == '/')
		free(path);
	return (0);
}
