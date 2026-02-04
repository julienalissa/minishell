#ifndef AST_H
# define AST_H

#include "../../include/struct.h"

t_ast	*build_ast(t_token *token, t_data *data);
t_ast	*creat_node(t_token	*token, t_data *data);
t_token	*find_lowest_prio(t_token *token);
void	expand_dollar(char *name, t_list **lst, t_data *data);
int		check_file(char *name, char *file);
void	creat_asterisk(t_list **current, t_list	**lst, char *namefile, int *flag);
void	creat_operator(t_token *temp, t_ast **node);
void	expand_asterisk(char *name, t_list **lst);
int		is_redir(t_token *token);
void	creat_redir(t_token	*temp, t_ast **node, t_token	*temp_redir);
void	addback_redir(t_redir **lst, t_redir *new);
void	choise_redir(t_redir **redir, t_token *temp_redir);
t_redir	*last_redir(t_redir *lst);


// To delet
void print_node_content(t_ast *node);
void print_tree_visual(t_ast *node, int space, char branch);

#endif
