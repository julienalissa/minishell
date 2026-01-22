#include "../../include/minishell.h"

t_token	*find_pivot(t_token *temp);
int	parantheses_counter(t_token	*temp);

t_token	*find_lowest_prio(t_token *token)
{
	t_token	*temp;
	t_token	*pivot;
	int		parantheses_count;

	parantheses_count = 0;
	temp = token;
	pivot = NULL;
	while(temp)
	{
		parantheses_count += parantheses_counter(temp);
		if (parantheses_count == 0)
			pivot = find_pivot(temp);
		temp = temp->next;
	}
	if (parantheses_count != 0)
		ft_error("Error: Paranthesis impaire\n"); // Penser à free
	return(pivot);
}

t_token	*find_pivot(t_token *temp)
{
	t_token *pivot;

	pivot = NULL;
	if (temp->token_type == TOKEN_AND || temp->token_type == TOKEN_OR)
		pivot = temp;
	else if (temp->token_type == TOKEN_PIPE)
	{
		if (!pivot || (temp->token_type != TOKEN_AND && temp->token_type != TOKEN_OR))
			pivot = temp;
	}
	return(pivot);
}

int	parantheses_counter(t_token	*temp)
{
	if (temp->token_type == TOKEN_PARENTHESIS_IN)
		return (1);
	else if (temp->token_type == TOKEN_PARENTHESIS_OUT)
		return (-1);
	return (0);
}
