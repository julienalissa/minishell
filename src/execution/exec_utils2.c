/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 07:28:50 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/16 08:26:28 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		return;
	if (dup2(fd, std_target) < 0)
		ft_error("Error: dup2 failed\n");
	close(fd);
}

int	command_count(t_ast *node)
{
	if (!node)
		return (0);
	if (node->op_type == NODE_CMD)
		return (1);
	return (command_count(node->left) + command_count(node->right));
}

// int	setup_heredocs(t_data *data, t_ast *node)
// {
// 	int		status;
// 	int		ret_status;

// 	ret_status = 0;
// 	status = 0;
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (prepare_heredocs(node, data) == -1)
// 		exit (data->last_exit_code);
// 	else
// 		exit (EXIT_SUCCESS);
// 	waitpid(-1, &status, 0);
// 	if (WIFEXITED(status))
// 		ret_status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		ret_status = 128 + WTERMSIG(status);
// 	signals();
// 	if (ret_status == 130 || ret_status == 131)
// 	{
// 		write(1, "\n", 1);
// 		data->last_exit_code = ret_status;
// 		return (-1);
// 	}
// 	else
// 		redir->
// 	return (0);
// }
