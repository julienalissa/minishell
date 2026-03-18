/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:12:43 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/18 09:25:29 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_syntax_errors(t_token *token, t_token *pivot, t_data *data,
		char *pivot_value)
{
	if (token == NULL || token == pivot)
	{
		ft_printf("-bash: syntax error near unexpected token `%s'\n",
			pivot_value);
		data->last_exit_code = 2;
		return (1);
	}
	if (!pivot->next)
	{
		ft_printf("-bash: syntax error near unexpected token `%s'\n",
			pivot_value);
		data->last_exit_code = 2;
		return (1);
	}
	return (0);
}

t_ast	*handle_no_pivot(t_token *token, t_token *end, t_data *data)
{
	t_token	*new_head;
	t_token	*new_end;

	if (token->token_type == TOKEN_PARENTHESIS_IN)
	{
		new_end = token;
		new_head = trim_paranthesis(token, end, &new_end);
		if (new_head == token || !new_head)
		{
			ft_printf("-bash: syntax error near unexpected token `)'\n");
			data->last_exit_code = 2;
			return (NULL);
		}
		return (build_ast(new_head, new_end, data));
	}
	else
		return (creat_node(token, end, data));
}

t_ast	*create_node_from_pivot(t_token *token, t_token *pivot, t_data *data,
		t_token *right_start)
{
	t_ast	*node;

	if (token == pivot || !right_start)
	{
		ft_printf("-bash: syntax error near unexpected token `%s'\n",
			pivot->value);
		data->last_exit_code = 2;
		return (NULL);
	}
	node = malloc(sizeof(t_ast));
	ft_bzero(node, sizeof(t_ast));
	creat_operator(pivot, &node);
	return (node);
}

t_ast	*build_ast(t_token *token, t_token *end, t_data *data)
{
	t_token	*pivot;
	t_token	*right_start;
	t_ast	*node;

	if (!token || token == end)
		return (NULL);
	pivot = find_lowest_prio(token, end);
	if (!pivot)
		return (handle_no_pivot(token, end, data));
	right_start = pivot->next;
	node = create_node_from_pivot(token, pivot, data, right_start);
	if (!node)
		return (NULL);
	node->left = build_ast(token, pivot, data);
	node->right = build_ast(right_start, end, data);
	if (!node->left || !node->right)
	{
		ft_printf("-bash: syntax error near unexpected token\n");
		data->last_exit_code = 2;
		free_node(node);
		return (NULL);
	}
	return (node);
}
