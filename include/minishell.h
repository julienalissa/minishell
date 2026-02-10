
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"
# include "../libft/libft.h"
# include "../src/ast/ast.h"
# include "../src/execution/exec.h"
# include <signal.h>
// Initialisation de la structure data
void set_data(t_data *data, char **env);

//Environnement
void	creat_env(t_data *data);
t_env	*lstnew_env(char *key, char *value);
void	lstadd_back_env(t_env **lst, t_env *new);
void	lstdel_env(t_env *env);
void	lstclear_env(t_data *data);

// Gestion variables d'environnement
void	print_env(t_env *env);
int		is_valid_export(char *str);
void	add_or_update_env(t_data *data, char *str);
void	creat_envp(t_data *data);
void	delete_env(t_data *data, char *key);
char	*get_env_value(t_data *data, char *key);
void	update_env_var(t_data *data, char *key, char *value);

//Tokenization
void	creat_token(char *line, t_data *data);
void	make_quotes(char *line, t_data *data);
char	*remove_quote(char *line, t_data *data, char quote);
t_token	*lstnew_token(char *tmp, t_states state);
void	lstadd_back_token(t_token **lst, t_token *new);
void	lstclear_token(t_token **lst);
void	lstdel_token(t_token *token);
t_token	*lstlast_token(t_token *lst);


// Builtins
int		echo(char **args);
int		cd(char **args, t_data *data);
int		pwd(void);
int	export(char **args, t_data *data);
int		unset(char **args, t_data *data);
int		env(t_data *data);
int		exit_42(char **args);

// Execution

void ft_free_str(char **str);

// Utilitaires
void	ft_error(char *msg);
void	ft_split_clear(char **split);

int	is_builtin(char *cmd);
int	execut_builtin(t_ast *node, t_data *data);

// Signaux
extern volatile sig_atomic_t	g_signal_received;
void	signals(void);

#endif
