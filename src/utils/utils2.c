/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:20:05 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/09 17:20:26 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_node(t_ast *node)
{
	t_redir	*temp_redir;

	if (!node)
		return ;
	free_node(node->left);
	free_node(node->right);
	if (node->args)
		ft_freetab(node->args);
	if (node->redir)
	{
		while (node->redir)
		{
			temp_redir = node->redir->next;
			free(node->redir->file);
			free(node->redir);
			node->redir = temp_redir;
		}
	}
	free(node);
}

void	free_all(t_data *data, t_ast *node, char *path)
{
	(void)node;
	if (path)
		free(path);
	if (data->save_ast)
		free_node(data->save_ast);
	if (data->exec && data->exec->pids)
	{
		free(data->exec->pids);
		data->exec->pids = NULL;
	}
}

void	free_child(t_data *data, char *path)
{
	if (path)
		free(path);
	if (data->save_ast)
		free_node(data->save_ast);
	if (data->envp)
		lstclear_env(data);
	if (data->exec && data->exec->pids)
	{
		free(data->exec->pids);
		free(data->exec);
	}
}
