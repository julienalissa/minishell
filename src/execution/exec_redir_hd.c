/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 07:56:52 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/11 12:59:17 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_heredocs(t_redir *redir, t_data *data);
static void	close_and_free(char *line, char *write_line, int fd_file, int flag);
static int	open_redir_hd(t_data *data, t_redir *redir);
static char	*line_to_write(t_env	*env_temp, char *line, t_data *data, t_redir *redir);

int	prepare_heredocs(t_ast *node, t_data *data)
{
	t_redir	*temp;

	if (!node)
		return (0);
	temp = node->redir;
	while (temp)
	{
		if (temp->redir_type == NODE_HEREDOC)
		{
			if (open_heredocs(temp, data) == -1)
				return (-1);
		}
		temp = temp->next;
	}
	if (prepare_heredocs(node->left, data) == -1)
		return (-1);
	if (prepare_heredocs(node->right, data) == -1)
		return (-1);
	return (1);
}

static int	open_heredocs(t_redir *redir, t_data *data)
{
	int	fd_filetemp;
	char	*line;
	char	*write_line;
	t_env	*env_temp;

	env_temp = data->env;
	fd_filetemp = open_redir_hd(data, redir);
	while (1)
	{
		write_line = NULL;
		line = readline("heredoc >");
		if (!line)
			break;
		if (ft_strcmp(line, redir->delimiter) == 0)
			break;
		write_line = line_to_write(env_temp, line, data, redir);
		ft_putendl_fd(write_line, fd_filetemp);
		close_and_free(line, write_line, fd_filetemp, 0);
		line = NULL;
	}
	close_and_free(line, write_line, fd_filetemp, 1);
	return (1);
}

static void	close_and_free(char *line, char *write_line, int fd_file, int flag)
{
	if (write_line)
		free(write_line);
	if (line)
		free(line);
	if (flag)
		close(fd_file);
}
static int	open_redir_hd(t_data *data, t_redir *redir)
{
	int		fd_w;
	char	*nb;

	nb = ft_itoa(data->i);
	redir->file = ft_strjoin("hd_temp", nb);
	fd_w = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd_w < 0)
		ft_error("heredoc: ");
	free(nb);
	data->i++;
	return (fd_w);
}

static char *line_to_write(t_env	*env_temp, char *line, t_data *data, t_redir *redir)
{
	char *res;

	res = NULL;
	if (redir->quote_hd == 0)
		res = result_expand(env_temp, line, data);
	else
		res = ft_strdup(line);
	return (res);
}




