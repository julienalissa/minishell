#include "../../include/minishell.h"

t_env	*lstlast_env(t_env *lst);

t_env	*lstnew_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = value;
	node->next = NULL;
	return (node);
}

void	lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	if (!*lst && !new)
		return ;
	temp = lstlast_env(*lst);
	if (temp)
		temp->next = new;
	else
		*lst = temp;
}

t_env	*lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstclear_env(t_data *data)
{
	t_env	*temp;

	if (!data->env)
		return ;
	while (data->env)
	{
		temp = data->env->next;
		lstdel_env(data->env);
		data->env = temp;
	}
}

void	lstdel_env(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->val)
		free(env->val);
	free (env);
}
