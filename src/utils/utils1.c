/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   utils1.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:24:09 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:24:10 by jualissa       ########   odam.nl        */
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
