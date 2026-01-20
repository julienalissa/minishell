#include "../../include/minishell.h"

void	lstclear_token(t_token **lst)
{
	t_token	*temp;

	if (!lst || !*lst)
		return;
	while (*lst)
	{
		temp = (*lst)->next;
		lstdel_token(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	lstdel_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free (token);
}
