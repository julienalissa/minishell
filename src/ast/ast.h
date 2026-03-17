/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:12:21 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/12 16:22:03 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../../include/minishell.h"
# include "../../include/struct.h"

typedef enum e_op_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}					t_op_type;

typedef enum e_redir_type
{
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_APPEND,
	NODE_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	char			*file;
	char			*delimiter;
	int				quote_hd;
	int				fd_hd;
	t_redir_type	redir_type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_ast
{
	char			**args;
	t_op_type		op_type;
	t_redir			*redir;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

t_ast				*build_ast(t_token *token, t_data *data);
t_ast				*creat_node(t_token *token, t_data *data);
t_token				*find_lowest_prio(t_token *token);
void				expand_dollar(char *name, t_list **lst, t_data *data);
void				creat_operator(t_token *temp, t_ast **node);
void				expand_asterisk(char *name, t_list **lst);
int					is_redir(t_token *token);
void				creat_redir(t_token *temp, t_ast **node,
						t_token *temp_redir);
void				addback_redir(t_redir **lst, t_redir *new);
void				choise_redir(t_redir **redir, t_token *temp_redir);
t_redir				*last_redir(t_redir *lst);

#endif
