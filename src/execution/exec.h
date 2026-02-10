#ifndef EXEC_H
# define EXEC_H

void	setup_exec(t_ast *node, t_data *data);
void	exec_ast(t_ast *node, t_data *data, int fd_in, int fd_out);
void	exec_pipe(t_ast *node, t_data *data, int fd_in, int fd_out);
void	exec_and(t_ast *node, t_data *data, int fd_in, int fd_out);
void	exec_or(t_ast *node, t_data *data, int fd_in, int fd_out);
char 	*find_path(t_ast *node, t_data *data);
int		wait_process(t_data *data);
void	wait_all_process(t_data *data);
void	define_redir(t_ast *node, int fd_in, int fd_out);
void	dup_and_close(int std_target, int fd);

#endif
