/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:24:09 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/16 14:11:18 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_data(t_data *data, char **env)
{
	ft_bzero(data, sizeof(t_data));
	data->envp = env;
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		return;
	ft_bzero(data->exec, sizeof(t_exec));
	data->exec->pids = NULL;
	data->exec->fd_to_close = -1;
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
