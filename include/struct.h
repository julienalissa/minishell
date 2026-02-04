#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_ast	t_ast;
typedef struct s_token	t_token;
typedef struct s_data	t_data;
typedef struct s_redir t_redir;

typedef enum e_token_type
{
	TOKEN_WORD, // 0
	TOKEN_PIPE,// 1
	TOKEN_REDIR_IN, // 2
	TOKEN_REDIR_OUT, // 3
	TOKEN_HEREDOC, // 4
	TOKEN_APPEND, //5
	TOKEN_AND, //6
	TOKEN_OR, //7
	TOKEN_PARENTHESIS_IN, //8
	TOKEN_PARENTHESIS_OUT,
}	t_token_type;

typedef enum e_states
{
	NORMAL,
	QUOTES,
	DQUOTES
}	t_states;

typedef struct s_token
{
	t_token_type	token_type;
	char			*value;
	t_states		states;
	struct			s_token *next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct	s_env	*next;
}					t_env;

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

typedef struct s_exec
{
	pid_t	*pids;
	int		prev_fd;
	int		nb_cmds;
	int		ret_status;
}			t_exec;

typedef struct s_data
{
	int			i;
	char		**envp;
	t_states	flag_states;
	t_token		*token;
	t_env		*env;
	t_exec		*exec;
}	t_data;

#endif
