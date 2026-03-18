/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:20:00 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/18 07:20:58 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_pipe(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	int	pipefd[2];
	int	save;

	if ((pipe(pipefd)) == -1)
		return ;
	data->exec->pipe_fds[data->exec->nb_pipe_fds++] = pipefd[0];
	data->exec->pipe_fds[data->exec->nb_pipe_fds++] = pipefd[1];
	save = data->exec->is_piped;
	data->exec->is_piped = 1;
	data->exec->fd_to_close = pipefd[0];
	exec_ast(node->left, data, fd_in, pipefd[1]);
	close(pipefd[1]);
	data->exec->fd_to_close = -1;
	exec_ast(node->right, data, pipefd[0], fd_out);
	close(pipefd[0]);
	data->exec->is_piped = save;
}

void	exec_and(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	exec_ast(node->left, data, fd_in, fd_out);
	wait_all_process(data);
	if (data->last_exit_code == 0)
	{
		exec_ast(node->right, data, fd_in, fd_out);
		wait_all_process(data);
	}
}

void	exec_or(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	exec_ast(node->left, data, fd_in, fd_out);
	wait_all_process(data);
	if (data->last_exit_code != 0)
	{
		exec_ast(node->right, data, fd_in, fd_out);
		wait_all_process(data);
	}
}

void	exec_script(t_data *data, t_ast *node, char *path)
{
	char	*sh_arg[3];

	sh_arg[0] = "/bin/sh";
	sh_arg[1] = path;
	sh_arg[2] = NULL;
	ft_freetab(node->args);
	execve("/bin/sh", sh_arg, data->envp);
}
