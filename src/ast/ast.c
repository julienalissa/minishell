#include "../../include/minishell.h"

t_token	*trim_paranthesis(t_token *token);
void	node_left(t_token *token, t_token *pivot);
void	free_pivot(t_token *pivot);

void	node_left(t_token *token, t_token *pivot)
{
	t_token	*temp;

	if (!token || token == pivot)
		return ;
	temp = token;
	while (temp && temp->next != pivot)
		temp = temp->next;
	if (temp)
		temp->next = NULL;
}

t_token	*trim_paranthesis(t_token *token)
{
	t_token	*start;
	t_token	*last;
	t_token	*temp;

	last = lstlast_token(token);
	if (!token || (token->token_type != TOKEN_PARENTHESIS_IN
			&& last->token_type != TOKEN_PARENTHESIS_OUT))
		return (token);
	start = token->next;
	lstdel_token(token);
	temp = start;
	while (temp)
	{
		if (temp->next == last)
		{
			temp->next = NULL;
			break ;
		}
		temp = temp->next;
	}
	lstdel_token(last);
	return (start);
}

void	free_pivot(t_token *pivot)
{
	if (!pivot)
		return ;
	if (pivot->value)
		free(pivot->value);
	free(pivot);
}
