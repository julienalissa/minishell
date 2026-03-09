/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:19:28 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/09 16:00:12 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void		exec_cmd(t_ast *node, t_data *data, int fd_in, int fd_out);
static void		setup_cmd(t_ast *node, t_data *data, int fd_in, int fd_out);
static void		setup_cmdd(t_ast *node, t_data *data, int fd_in, int fd_out);

void	setup_exec(t_ast *node, t_data *data)
{
	int	total_cmds;

	if (!node)
		return ;
	total_cmds = command_count(node);
	data->exec->pids = malloc(sizeof(pid_t) * total_cmds);
	if (!data->exec->pids)
		return ;
	data->exec->nb_cmds = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec_ast(node, data, STDIN_FILENO, STDOUT_FILENO);
	wait_all_process(data);
	if (data->last_exit_code == 130 || data->last_exit_code == 131)
		write(1, "\n", 1);
	signals();
	free_all(data, node, NULL);
}

void	exec_ast(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	if (!node)
		return ;
	if (node->op_type == NODE_PIPE)
		exec_pipe(node, data, fd_in, fd_out);
	else if (node->op_type == NODE_AND)
		exec_and(node, data, fd_in, fd_out);
	else if (node->op_type == NODE_OR)
		exec_or(node, data, fd_in, fd_out);
	else if (node->op_type == NODE_CMD)
		setup_cmd(node, data, fd_in, fd_out);
}

static void	exec_cmd(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	define_redir(node, fd_in, fd_out);
	path = find_path(node, data);
	if (!path)
	{
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_child(data, path);
		exit(127);
	}
	execve(path, node->args, data->envp);
	if (errno == ENOEXEC)
		exec_script(data, node, path);
	perror(node->args[0]);
	free_child(data, path);
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}

static void	setup_cmd(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	int	save_stdin;
	int	save_stdout;

	if (is_builtin(node->args[0]) && (data->exec->is_piped == 0))
	{
		save_stdin = dup(STDIN_FILENO);
		save_stdout = dup(STDOUT_FILENO);
		if (save_stdin < 0 || save_stdout < 0)
			ft_error("Error: dup failed\n");
		define_redir(node, fd_in, fd_out);
		data->last_exit_code = execut_builtin(node, data);
		dup_and_close(STDIN_FILENO, save_stdin);
		dup_and_close(STDOUT_FILENO, save_stdout);
		if (data->need_exit)
		{
			free_all(data, node, NULL);
			lstclear_env(data);
			exit(data->save_status);
		}
	}
	else
		setup_cmdd(node, data, fd_in, fd_out);
}

static void	setup_cmdd(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	data->exec->pids[data->exec->nb_cmds] = fork();
	if ((data->exec->pids[data->exec->nb_cmds]) == 0)
	{
		if (data->exec->fd_to_close != -1)
			close(data->exec->fd_to_close);
		if (is_builtin(node->args[0]) && (data->exec->is_piped == 1))
		{
			define_redir(node, fd_in, fd_out);
			data->last_exit_code = execut_builtin(node, data);
			free_child(data, NULL);
			exit(data->last_exit_code);
		}
		else
			exec_cmd(node, data, fd_in, fd_out);
	}
	data->exec->nb_cmds++;
}
