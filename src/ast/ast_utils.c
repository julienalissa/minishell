/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:12:31 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/18 09:18:50 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_token	*find_lowest_prio(t_token *token, t_token *end)
{
	t_token	*temp;
	t_token	*pivot;
	int		parantheses_count;

	parantheses_count = 0;
	temp = token;
	pivot = NULL;
	while (temp && temp != end)
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
