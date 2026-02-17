#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PARENTHESIS_IN,
	TOKEN_PARENTHESIS_OUT,
}					t_token_type;

typedef enum e_states
{
	NORMAL,
	QUOTES,
	DQUOTES
}					t_states;

typedef struct s_token
{
	t_token_type	token_type;
	char			*value;
	t_states		states;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}					t_env;

typedef struct s_exec
{
	pid_t			*pids;
	int				nb_cmds;
	int				ret_status;
	int				is_piped;
}					t_exec;

typedef struct s_data
{
	int				i;
	char			**envp;
	int				last_exit_code;
	t_states		flag_states;
	t_token			*token;
	t_env			*env;
	t_exec			*exec;
}					t_data;

#endif
