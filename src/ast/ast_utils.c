#include "../../include/minishell.h"

int		parantheses_counter(t_token *temp);

t_token	*check_pivot(t_token *pivot, t_token *temp)
{
	if (temp->token_type == TOKEN_AND || temp->token_type == TOKEN_OR)
		pivot = temp;
	else if (temp->token_type == TOKEN_PIPE)
	{
		if (!pivot || pivot->token_type == TOKEN_PIPE)
			pivot = temp;
	}
	return (pivot);
}

t_token	*find_lowest_prio(t_token *token)
{
	t_token	*temp;
	t_token	*pivot;
	int		parantheses_count;

	parantheses_count = 0;
	temp = token;
	pivot = NULL;
	while (temp)
	{
		parantheses_count += parantheses_counter(temp);
		if (parantheses_count == 0)
			pivot = check_pivot(pivot, temp);
		temp = temp->next;
	}
	if (parantheses_count != 0)
		return (NULL);
	return (pivot);
}

int	parantheses_counter(t_token *temp)
{
	if (temp->token_type == TOKEN_PARENTHESIS_IN)
		return (1);
	else if (temp->token_type == TOKEN_PARENTHESIS_OUT)
		return (-1);
	return (0);
}
