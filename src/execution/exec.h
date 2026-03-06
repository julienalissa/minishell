/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:19:53 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/06 10:42:05 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../include/minishell.h"

void	setup_exec(t_ast *node, t_data *data);
void	exec_ast(t_ast *node, t_data *data, int fd_in, int fd_out);
void	exec_pipe(t_ast *node, t_data *data, int fd_in, int fd_out);
void	exec_and(t_ast *node, t_data *data, int fd_in, int fd_out);
void	exec_or(t_ast *node, t_data *data, int fd_in, int fd_out);
char	*find_path(t_ast *node, t_data *data);
int		wait_process(t_data *data);
void	wait_all_process(t_data *data);
int		command_count(t_ast *node);
void	define_redir(t_ast *node, int fd_in, int fd_out);
void	dup_and_close(int std_target, int fd);
void	exec_script(t_data *data, t_ast *node, char *path);
int		open_redir_hd(char *delimiter, int final_in, int fd_in);

#endif
