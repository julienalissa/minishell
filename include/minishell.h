#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"
# include "../libft/libft.h"
# include "../src/ast/ast.h"



// Environnement
void	creat_env(t_data *data);
t_env	*lstnew_env(char *key, char *value);
void	lstadd_back_env(t_env **lst, t_env *new);
void	lstdel_env(t_env *env);
void	lstclear_env(t_data *data);

// Tokenization
void	creat_token(char *line, t_data *data);
void	make_quotes(char *line, t_data *data);
char	*remove_quote(char *line, t_data *data, char quote);
t_token	*lstnew_token(char *tmp, t_states state);
void	lstadd_back_token(t_token **lst, t_token *new);
void	lstclear_token(t_token **lst);
void	lstdel_token(t_token *token);
t_token	*lstlast_token(t_token *lst);

// Utils
void	ft_error(char *errorname);
void	set_data(t_data *data, char **env);

#endif
