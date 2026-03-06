/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 07:56:52 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/06 08:09:27 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	hd_finish(int fd_write);

int	open_redir_hd(char *delimiter, int final_in, int fd_in)
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
			return (hd_finish(fd_write));
		ft_putstr_fd(line, fd_write);
	}
	close(fd_write);
	if ((fd_rd = open(".hd_tmp", O_RDONLY)) < 0)
		ft_error("Error : can't read in [.hd_tmp]\n");
	unlink(".hd_tmp");
	return (fd_rd);
}

static int	hd_finish(int fd_write)
{
	int	fd_rd;

	fd_rd = 0;
	close(fd_write);
	if ((fd_rd = open(".hd_tmp", O_RDONLY)) < 0)
		ft_error("Error : can't read in [.hd_tmp]\n");
	unlink(".hd_tmp");
	return (fd_rd);
}
