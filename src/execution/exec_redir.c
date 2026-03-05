/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:20:06 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/05 14:37:18 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>

static int	open_redir_out(char *file, int final_out, int fd_out);
static int	open_redir_in(char *file, int final_in, int fd_in);
static int	open_redir_append(char *file, int final_out, int fd_out);
static int	open_redir_hd(char *delimiter, int final_in, int fd_in);

void	define_redir(t_ast *node, int fd_in, int fd_out)
{
	t_redir	*tmp;
	int		final_in;
	int		final_out;

	tmp = node->redir;
	final_in = fd_in;
	final_out = fd_out;
	while (tmp)
	{
		if (tmp && tmp->redir_type == NODE_REDIR_IN)
			final_in = open_redir_in(tmp->file, final_in, fd_in);
		else if (tmp && tmp->redir_type == NODE_HEREDOC)
			final_in = open_redir_hd(tmp->file, final_in, fd_in);
		else if (tmp && tmp->redir_type == NODE_REDIR_OUT)
			final_out = open_redir_out(tmp->file, final_out, fd_out);
		else if (tmp && tmp->redir_type == NODE_APPEND)
			final_out = open_redir_append(tmp->file, final_out, fd_out);
		tmp = tmp->next;
	}
	dup_and_close(0, final_in);
	dup_and_close(1, final_out);
}

static int	open_redir_in(char *file, int final_in, int fd_in)
{
	int	ret_in;

	if (final_in)
	{
		if (final_in != fd_in && final_in > 2)
			close(final_in);
	}
	ret_in = open(file, O_RDONLY);
	if (ret_in < 0)
		ft_error("error: redir_in\n");
	return (ret_in);
}

static int	open_redir_out(char *file, int final_out, int fd_out)
{
	int	ret_out;

	if (final_out)
	{
		if (final_out != fd_out && final_out > 2)
			close(final_out);
	}
	ret_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ret_out < 0)
		ft_error("Error: redir_out\n");
	return (ret_out);
}

static int	open_redir_append(char *file, int final_out, int fd_out)
{
	int	ret_append;

	if (final_out)
	{
		if (final_out != fd_out && final_out > 2)
			close(final_out);
	}
	ret_append = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ret_append < 0)
		ft_error("Error: redir_append\n");
	return (ret_append);
}

static int	open_redir_hd(char *delimiter, int final_in, int fd_in)
{
	int		fd_write;
	int		fd_rd;
	char	*line;
	char	buffer[1024];
	int		n;

	if (final_in != fd_in && final_in > 2)
		close(final_in);
	if ((fd_write = open(".hd_tmp", O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
		ft_error("Error: can't write in [.hd_tmp]\n");
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		n = read(STDIN_FILENO, buffer, 1023);
		if (n <= 0)
			break ;
		buffer[n] = '\0';
		line = buffer;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& (line[ft_strlen(delimiter)] == '\n'
				|| line[ft_strlen(delimiter)] == '\0'))
		{
			close(fd_write);
			if ((fd_rd = open(".hd_tmp", O_RDONLY)) < 0)
				ft_error("Error : can't read in [.hd_tmp]\n");
			unlink(".hd_tmp");
			return (fd_rd);
		}
		ft_putstr_fd(line, fd_write);
	}
	close(fd_write);
	if ((fd_rd = open(".hd_tmp", O_RDONLY)) < 0)
		ft_error("Error : can't read in [.hd_tmp]\n");
	unlink(".hd_tmp");
	return (fd_rd);
}
