#include "../../include/minishell.h"

t_token	*trim_paranthesis(t_token *token);
void	node_left(t_token *token, t_token *pivot);
void	free_pivot(t_token *pivot);

t_ast	*build_ast(t_token *token, t_data *data)
{
	t_token	*pivot;
	t_token	*right_start;
	t_ast	*node;
	char	*pivot_value;

	if (!token)
		return (NULL);
	pivot = find_lowest_prio(token);
	if (pivot == NULL)
	{
		if (token->token_type == TOKEN_PARENTHESIS_IN)
		{
			token = trim_paranthesis(token);
			return (build_ast(token, data));
		}
		else
		{
			node = creat_node(token, data);
			return (node);
		}
	}
	right_start = pivot->next;
	node_left(token, pivot);
	pivot_value = ft_strdup(pivot->value);
	if (token == NULL || token == pivot)
	{
		ft_printf("-bash: syntax error near unexpected token `%s'\n",
			pivot_value);
		data->last_exit_code = 2;
		free(pivot_value);
		return (NULL);
	}
	node = malloc(sizeof(t_ast));
	ft_bzero(node, sizeof(t_ast));
	creat_operator(pivot, &node);
	pivot_value = ft_strdup(pivot->value);
	free_pivot(pivot);
	if (right_start == NULL)
	{
		ft_printf("-bash: syntax error near unexpected token `%s'\n",
			pivot_value);
		data->last_exit_code = 2;
		free(node);
		free(pivot_value);
		return (NULL);
	}
	node->left = build_ast(token, data);
	node->right = build_ast(right_start, data);
	if (node->left == NULL || node->right == NULL)
	{
		ft_printf("-bash: syntax error near unexpected token `%s'\n",
			pivot_value);
		data->last_exit_code = 2;
		free(node);
		free(pivot_value);
		return (NULL);
	}
	free(pivot_value);
	return (node);
}

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
