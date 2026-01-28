#ifndef EXEC_H
# define EXEC_H

#include "../../include/minishell.h"


typedef struct s_exec
{
	pid_t	*pids;
	int		prev_fd;
	int		nb_cmds;
	int		ret_status;
}			t_exec;

void	exec_ast(t_ast *node, t_exec *exec, int fd_in, int fd_out);
int		wait_process(t_exec *exec);
void	define_redir(t_ast *node, int fd_in, int fd_out);
void	dup_and_close(int old_fd, int new_fd);

#endif
