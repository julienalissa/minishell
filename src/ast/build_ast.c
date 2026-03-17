/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:12:43 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/09 15:26:13 by lucasdebarn      ###   ########.fr       */
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

t_ast	*handle_no_pivot(t_token *token, t_data *data)
{
	t_token	*new_head;
	t_token	*old_head;

	if (token->token_type == TOKEN_PARENTHESIS_IN)
	{
		old_head = token;
		new_head = trim_paranthesis(token);
		if (new_head == old_head)
		{
			ft_printf("-bash: syntax error near unexpected token `)'\n");
			data->last_exit_code = 2;
			return (NULL);
		}
		if (old_head == data->token)
			data->token = new_head;
		if (!new_head)
		{
			ft_printf("-bash: syntax error near unexpected token `)'\n");
			data->last_exit_code = 2;
			return (NULL);
		}
		return (build_ast(new_head, data));
	}
	else
		return (creat_node(token, data));
}

t_ast	*create_node_from_pivot(t_token *token, t_token *pivot, t_data *data,
		t_token *right_start)
{
	t_ast	*node;
	char	*pivot_value;

	node_left(token, pivot);
	pivot_value = ft_strdup(pivot->value);
	if (!pivot_value || token == pivot || !right_start)
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
	free_pivot(pivot);
	free(pivot_value);
	return (node);
}

t_ast	*build_ast(t_token *token, t_data *data)
{
	t_token	*pivot;
	t_token	*right_start;
	t_ast	*node;

	if (!token)
		return (NULL);
	pivot = find_lowest_prio(token);
	if (!pivot)
		return (handle_no_pivot(token, data));
	right_start = pivot->next;
	node = create_node_from_pivot(token, pivot, data, right_start);
	if (!node)
		return (NULL);
	node->left = build_ast(token, data);
	node->right = build_ast(right_start, data);
	lstclear_token(&right_start);
	if (!node->left || !node->right)
	{
		ft_printf("-bash: syntax error near unexpected token\n");
		data->last_exit_code = 2;
		free_node(node);
		return (NULL);
	}
	return (node);
}
