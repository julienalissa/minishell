/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:24:09 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/18 09:41:05 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_data(t_data *data, char **env)
{
	ft_bzero(data, sizeof(t_data));
	data->envp = env;
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		return ;
	ft_bzero(data->exec, sizeof(t_exec));
	data->exec->pids = NULL;
	data->exec->fd_to_close = -1;
	data->exec->nb_pipe_fds = 0;
	creat_env(data);
	if (env && env[0])
		add_shlvl(data);
}

void	ft_error(char *errorname)
{
	perror(errorname);
	exit(EXIT_FAILURE);
}

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	close_pipe_fds(t_data *data, int fd_in, int fd_out)
{
	int	i;

	i = 0;
	while (i < data->exec->nb_pipe_fds)
	{
		if (data->exec->pipe_fds[i] != fd_in
			&& data->exec->pipe_fds[i] != fd_out)
			close(data->exec->pipe_fds[i]);
		i++;
	}
}
