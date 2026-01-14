#include "minishell.h"

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
	TOKEN_PARENTHESIS_OUT //9
} t_token_type;

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

typedef struct s_data
{
	int			i;
	char		**envp;
	t_states	flag_states;
	t_token		*token;
	t_env		*env;
}	t_data;

