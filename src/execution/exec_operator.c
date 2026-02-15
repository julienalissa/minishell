#include "../../include/minishell.h"

void	exec_pipe(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	int	pipefd[2];
	int	save;

	if ((pipe(pipefd)) == -1)
		return ;
	save = data->exec->is_piped;
	data->exec->is_piped = 1;
	exec_ast(node->left, data, fd_in, pipefd[1]);
	close(pipefd[1]);
	exec_ast(node->right, data, pipefd[0], fd_out);
	close(pipefd[0]);
	data->exec->is_piped = save;
}

void	exec_and(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	exec_ast(node->left, data, fd_in, fd_out);
	if ((data->exec->ret_status = (wait_process(data))) == 0)
		exec_ast(node->right, data, fd_in, fd_out);
}

void	exec_or(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	exec_ast(node->left, data, fd_in, fd_out);
	if ((data->exec->ret_status = (wait_process(data))) != 0)
		exec_ast(node->right, data, fd_in, fd_out);
}
