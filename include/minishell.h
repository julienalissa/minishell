#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "struct.h"

// Environnement
void	creat_env(t_data *data);
t_env	*lstnew_env(char *key, char *value);
void	lstadd_back_env(t_env **lst, t_env *new);
void	lstdel_env(t_env *env);
void	lstclear_env(t_data **data);

// Tokenization
void		creat_token(char *line, t_data *data);
void		lstadd_back_token(t_token **lst, t_token *new);
t_token		*lstnew_token(char *tmp, t_data *data);
void		lstdel_token(t_token *token);
void		lstclear_token(t_data **data);

// Utils
void	ft_error(char *errorname);
void	set_data(t_data *data, char **env);

#endif
