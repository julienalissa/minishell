#include "../include/minishell.h"

t_token	*ft_lstnew_token(char *tmp)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = ft_strdup(tmp);
	define_token(node);
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	if (!lst && !new)
		return ;
	temp = ft_lstlast_token(*lst);
	if (temp)
		temp->next = new;
	else
		*lst = temp;
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear_token(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		*lst = temp;
	}
}
