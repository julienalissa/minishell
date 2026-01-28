#include "ast.h"

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
		{
			if (temp->token_type == TOKEN_AND || temp->token_type == TOKEN_OR)
				pivot = temp;
			else if (temp->token_type == TOKEN_PIPE)
			{
				if (!pivot || (temp->token_type != TOKEN_AND && temp->token_type != TOKEN_OR))
					pivot = temp;
			}
		}
		temp = temp->next;
	}
	if (parantheses_count != 0)
		ft_error("Error: Paranthesis impaire\n"); // Penser à free
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
