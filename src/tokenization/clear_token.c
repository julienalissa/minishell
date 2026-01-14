#include "../../include/minishell.h"

void	lstclear_token(t_data **data)
{
	t_token	*temp;

	if (!(*data)->token)
		return ;
	while ((*data)->token)
	{
		temp = (*data)->token->next;
		lstdel_token((*data)->token);
		(*data)->token = temp;
	}
}

void	lstdel_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free (token);
}
