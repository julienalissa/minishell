#include "../../include/minishell.h"

// TODO exec_cmd a finir , ensuite regarder avec prompt simple CMD | CMD
// Regarde le fonctionnement pour les heredocs et les appends
void	exec_ast(t_ast *node, t_exec *exec, int fd_in, int fd_out)
{
	if (!node)
		return ;
	if (node->op_type == NODE_PIPE)
		exec_pipe(node, exec, fd_in, fd_out);
	else if (node->op_type == NODE_AND)
		exec_and(node, exec, fd_in, fd_out);
	else if (node->op_type == NODE_OR)
		exec_or(node, exec, fd_in, fd_out);
	else if (node->op_type == NODE_CMD)
	{
		exec->pids[exec->nb_cmds] = fork() ;
		if ((exec->pids[exec->nb_cmds]) == 0)
			exec_cmd(node, exec, fd_in, fd_out);
		exec->nb_cmds++;
	}
}

void	exec_cmd(t_ast *node, t_exec *exec, int fd_in, int fd_out)
{
	char	*path;
	define_redir(node, fd_in, fd_out);
	path = get_path(node);
}

void	exec_pipe(t_ast *node, t_exec *exec, int fd_in, int fd_out)
{
	int	pipefd[2];

	pipe(pipefd);
	exec_ast(node->left, exec, fd_in, pipefd[1]);
	close (pipefd[1]);
	if ((exec->ret_status = wait_process(exec)) == 0);
	{
		exec_ast(node->right, exec, pipefd[0], fd_out);
		close (pipefd[0]);
	}
}

void	exec_and(t_ast *node, t_exec *exec, int fd_in, int fd_out)
{
	exec_ast(node->left, exec, fd_in, fd_out);
	if ((exec->ret_status = (wait_process(exec))) == 0)
		exec_ast(node->right, exec, fd_in, fd_out);
}

void	exec_or(t_ast *node, t_exec *exec, int fd_in, int fd_out)
{
	exec_ast(node->left, exec, fd_in, fd_out);
	if ((exec->ret_status = (wait_process(exec))) != 0)
		exec_ast(node->right, exec, fd_in, fd_out);
}

