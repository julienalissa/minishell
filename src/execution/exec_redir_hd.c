/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 07:56:52 by lucasdebarn       #+#    #+#             */
/*   Updated: 2026/03/16 13:52:17 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_heredocs(t_redir *redir, t_data *data);
static void	close_and_free(char *line, char *write_line, int *fdpipe, int flag);
static char	*line_to_write(char *line, t_data *data, t_redir *redir);
static void	heredocs_child(t_data *data, t_redir *redir, int *fdpipe);

int	prepare_heredocs(t_ast *node, t_data *data)
{
	t_redir	*temp;

	if (!node)
		return (0);
	if (node->redir)
	{
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
	}
	if (prepare_heredocs(node->left, data) == -1)
		return (-1);
	if (prepare_heredocs(node->right, data) == -1)
		return (-1);
	return (1);
}

static int	open_heredocs(t_redir *redir, t_data *data)
{
	int		fdpipe[2];
	pid_t	pid;
	int		ret_status;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(fdpipe) < 0)
		return (-1);
	ret_status = 0;
	pid = fork();
	if (pid == 0)
		heredocs_child(data, redir, fdpipe);
	close(fdpipe[1]);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		ret_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret_status = 128 + WTERMSIG(status);
	signals();
	if (ret_status == 130 || ret_status == 131)
	{
		write(1, "\n", 1);
		data->last_exit_code = ret_status;
		return (-1);
	}
	else
	{
		redir->fd_hd = fdpipe[0];
		if (redir->fd_hd < 0)
			return(-1);
	}
	return (1);
}

static void	close_and_free(char *line, char *write_line, int *fdpipe, int flag)
{
	if (write_line)
		free(write_line);
	if (line)
		free(line);
	if (flag)
		close(fdpipe[1]);
}

static char	*line_to_write(char *line, t_data *data, t_redir *redir)
{
	char	*res;
	t_env	*env_temp;

	env_temp = data->env;
	res = NULL;
	if (redir->quote_hd == 0)
		res = result_expand(env_temp, line, data);
	else
		res = ft_strdup(line);
	return (res);
}

void	heredocs_child(t_data *data, t_redir *redir, int *fdpipe)
{
	char	*line;
	char	*write_line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fdpipe[0]);
	while (1)
	{
		write_line = NULL;
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->delimiter) == 0)
			break ;
		write_line = line_to_write(line, data, redir);
		ft_putendl_fd(write_line, fdpipe[1]);
		close_and_free(line, write_line, fdpipe, 0);
		line = NULL;
	}
	rl_clear_history();
	close_and_free(line, write_line, fdpipe, 1);
	exit(EXIT_SUCCESS);
}
