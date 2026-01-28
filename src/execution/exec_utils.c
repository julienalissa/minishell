#include "exec.h"

int	wait_process(t_exec *exec)
{
	int	status;
	int	ret_status;

	waitpid(exec->pids[exec->nb_cmds], status, 0);
	if (WIFEXITED(status))
		ret_status = WEXITSTATUS(status);
	return(ret_status);
}

void	define_redir(t_ast *node, int fd_in, int fd_out)
{
	int	redir;

	redir = 0;
	if (node->redir == NULL)
	{
		dup_and_close(0, fd_in);
		dup_and_close(1, fd_out);
	}
	else if (node->redir->redir_type == NODE_REDIR_IN)
	{
		redir = open(node->redir->file);
		dup_and_close(0, redir);
		dup_and_close(1, fd_out);
	}
	else if (node->redir->redir_type == NODE_REDIR_OUT)
	{
		redir = open(node->redir->file);
		dup_and_close(0, fd_in);
		dup_and_close(1, redir);
	}
}
void	dup_and_close(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
		return;
	close(old_fd);
}

