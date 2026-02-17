#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "../src/ast/ast.h"
# include "../src/execution/exec.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Initialisation de la structure data
void							set_data(t_data *data, char **env);

// Environnement
void							creat_env(t_data *data);
char							*define_key(char *env);
char							*define_value(char *env);
t_env							*lstnew_env(char *key, char *value);
void							lstadd_back_env(t_env **lst, t_env *new);
void							lstdel_env(t_env *env);
void							lstclear_env(t_data *data);

// Gestion variables d'environnement
void							print_env(t_env *env);
int								is_valid(char *str);
int								is_valid_export(char *str);
void							add_or_update_env(t_data *data, char *str);
void							creat_envp(t_data *data);
int								count_env(t_env *env);
char							**alloc_envp(t_env *env, int count);
char							*create_env_str(t_env *env);
void							delete_env(t_data *data, char *key);
char							*get_env_value(t_data *data, char *key);
void							update_env_var(t_data *data, char *key,
									char *value);

// Tokenization
void							creat_token(char *line, t_data *data);
void							make_quotes(char *line, t_data *data);
char							*remove_quote(char *line, t_data *data,
									char quote);
t_token							*lstnew_token(char *tmp, t_states state);
void							lstadd_back_token(t_token **lst, t_token *new);
void							lstclear_token(t_token **lst);
void							lstdel_token(t_token *token);
t_token							*lstlast_token(t_token *lst);

// AST Node Creation
void							creat_lst(t_token *token, t_data *data, t_list **args_lst);
void							creat_cmd_node(t_list *args_lst, t_ast **node);
t_token							*trim_paranthesis(t_token *token);
void							node_left(t_token *token, t_token *pivot);
void							free_pivot(t_token *pivot);

// Builtins
int								echo(char **args);
int								cd(char **args);
int								pwd(void);
int								export(char **args, t_data *data);
int								unset(char **args, t_data *data);
int								env(t_data *data);
int								exit_42(t_ast *node, t_data *data);

// Utilitaires
void							ft_error(char *msg);
void							ft_split_clear(char **split);
void							free_node(t_ast *node);
void							ft_freetab(char **tab);

int								is_builtin(char *cmd);
int								execut_builtin(t_ast *node, t_data *data);

// Signaux
extern volatile sig_atomic_t	g_signal_received;
void							signals(void);

#endif
