/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:55:57 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/17 17:05:22 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "../src/ast/ast.h"
# include "../src/execution/exec.h"
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_signal_exit;

// Environnement
void		creat_env(t_data *data);
char		*define_key(char *env);
char		*define_value(char *env);
t_env		*lstnew_env(char *key, char *value);
void		lstadd_back_env(t_env **lst, t_env *new);
void		lstdel_env(t_env *env);
void		lstclear_env(t_data *data);
void		no_env(t_data *data);
void		add_shlvl(t_data *data);

// Gestion variables d'environnement
void		add_or_update_env(t_data *data, char *str);
int			count_env(t_env *env);
char		**alloc_envp(t_env *env, int count);
char		*create_env_str(t_env *env);
char		**get_current_env(t_data *data);
int			lstsize_env(t_env *env);
char		*define_key(char *env);
char		*define_value(char *env);

// Tokenization
void		creat_token(char *line, t_data *data);
void		make_quotes(char *line, t_data *data);
char		*remove_quote(char *line, t_data *data,
				char quote);
t_token		*lstnew_token(char *tmp, t_states state);
void		lstadd_back_token(t_token **lst, t_token *new);
void		lstclear_token(t_token **lst);
void		lstdel_token(t_token *token);
t_token		*lstlast_token(t_token *lst);
int			get_word(char *line, t_data *data);
char		*remove_escape(char *str);

// AST Node Creation
void		creat_lst(t_token *token, t_data *data, t_list **args_lst);
void		creat_cmd_node(t_list *args_lst, t_ast **node);
t_token		*trim_paranthesis(t_token *token);
void		node_left(t_token *token, t_token *pivot);
void		free_pivot(t_token *pivot);
char		*result_expand(t_env *env_temp, char *name, t_data *data);

// Builtins
int			echo(char **args, t_data *data);
int			cd(char **args, t_data *data);
int			pwd(void);
int			export(char **args, t_data *data);
int			unset(char **args, t_data *data);
int			env(t_data *data);
int			exit_42(t_ast *node, t_data *data);
int			is_valid(char *str);
void		copy_it(t_env *tmp, t_env **tab);
void		bbsort_it(int count, t_env **tab);
void		print_export_sorted(t_env *env);
void		parse_args(char *arg, char **key, char **val);
t_env		*check_env(t_env *env, char *key);
int			make_home(char *home_val, char **val, char *key);
int			error_ret(char **args, char *path, int ret);

// Utilitaires
void		set_data(t_data *data, char **env);
void		ft_error(char *msg);
void		free_node(t_ast *node);
void		ft_freetab(char **tab);
void		free_all(t_data *data, t_ast *node, char *path);
void		free_child(t_data *data, char *path, int fd_in, int fd_out);
int			is_builtin(char *cmd);
int			execut_builtin(t_ast *node, t_data *data);
void		free_redir(t_redir	*redir);
char		*ft_strjoin_free_s1(char *s1, char *s2);

// Signaux
void		signals(void);

#endif
