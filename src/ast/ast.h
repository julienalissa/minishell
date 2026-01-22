#include "../../include/minishell.h"

typedef enum e_op_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_op_type;

typedef enum e_redir_type
{
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_APPEND,
	NODE_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	char			*file;
	t_redir_type	redir_type;
	struct	s_redir	*next;
}					t_redir;

typedef struct s_ast
{
	char			**args;
	t_op_type		op_type;
	t_redir			*redir;
	struct	s_ast	*left;
	struct	s_ast	*right;

}					t_ast;

t_ast	*build_ast(t_token *token, t_data *data);
t_ast	*creat_node(t_token	*token, t_data *data);
t_token	*find_lowest_prio(t_token *token);
void	expand_dollar(char *name, t_list **lst, t_data *data);
int		check_file(char *name, char *file);
void	creat_asterisk(t_list **current, t_list	**lst, char *namefile, int *flag);
void	expand_asterisk(char *name, t_list **lst);
