#include "../../include/minishell.h"

t_token	*trim_paranthesis(t_token	*token);
void	node_left(t_token *token, t_token *pivot);

t_ast	*build_ast(t_token *token, t_data *data)
{
	t_token	*pivot;
	t_token	*right_start;
	t_ast	*node;

	if (!token)
		return(NULL);
	pivot = find_lowest_prio(token);
	if (pivot == NULL)
	{
		if (token->token_type == TOKEN_PARENTHESIS_IN)
		{
			token = trim_paranthesis(token);
			return(build_ast(token, data));
		}
		else
		{
			node = creat_node(token, data);
			return(node);
		}
	}
	right_start = pivot->next;
	node_left(token, pivot);
	free(pivot);
	node->left = build_ast(token, data);
	node->right = build_ast(right_start, data);
	return (node);
}

void	node_left(t_token *token, t_token *pivot)
{
	t_token *temp;

	if (!token)
		return ;
	temp = token;
	while(temp && temp->next != pivot)
		temp = temp->next;
	temp->next = NULL;
}

t_token	*trim_paranthesis(t_token *token)
{
	t_token	*start;
	t_token	*last;
	t_token	*temp;

	last = lstlast_token(token);
	if (!token || (token->token_type != TOKEN_PARENTHESIS_IN && last->token_type != TOKEN_PARENTHESIS_OUT))
		return (token);
	start = token->next;
	lstdel_token(token);
	temp = start;
	while(temp)
	{
		if (temp->next == last)
		{
			temp->next = NULL;
			break;
		}
		temp = temp->next;
	}
	lstdel_token(last);
	return(start);
}
