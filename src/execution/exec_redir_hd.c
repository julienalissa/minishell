/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 07:56:52 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/10 17:54:36 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	del_finded(int fd_write);
static int	del_not_find(int fd_write);
static char	*get_line(t_data *data, char *buffer, int n);

int	open_redir_hd(t_data *data, char *delimiter, int final_in, int fd_in)
{
	int		fd_write;
	char	*line;
	char	buffer[1024];
	int		n;

	if (final_in != fd_in && final_in > 2)
		close(final_in);
	fd_write = open(".hd_tmp", O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd_write < 0)
		ft_error("Error: can't write in [.hd_tmp]\n");
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		n = read(STDIN_FILENO, buffer, 1023);
		if (n <= 0)
			break ;
		buffer[n] = '\0';
		line = get_line(data, buffer, n);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& (line[ft_strlen(delimiter)] == '\n'
				|| line[ft_strlen(delimiter)] == '\0'))
			return (del_finded(fd_write));
		ft_putstr_fd(line, fd_write);
	}
	return (del_not_find(fd_write));
}

static int	del_finded(int fd_write)
{
	int	fd_rd;

	fd_rd = 0;
	close(fd_write);
	fd_rd = open(".hd_tmp", O_RDONLY);
	if (fd_rd < 0)
		ft_error("Error : can't read in [.hd_tmp]\n");
	unlink(".hd_tmp");
	return (fd_rd);
}

static int	del_not_find(int fd_write)
{
	int	fd_rd;

	fd_rd = 0;
	close(fd_write);
	fd_rd = open(".hd_tmp", O_RDONLY);
	if (fd_rd < 0)
		ft_error("Error : can't read in [.hd_tmp]\n");
	unlink(".hd_tmp");
	return (fd_rd);
}
static char	*get_line(t_data *data, char *buffer, int n)
{
	t_list	*lst;
	// char	*res;

	(void)n;
	lst = NULL;
	if (buffer[0] != '\'' && ft_strchr(buffer, '$'))
		expand_dollar(buffer, &lst, data);
	printf("%s\n", (char *)lst->content);
	return (buffer);
}
