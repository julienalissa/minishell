/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:12:15 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/18 09:40:30 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*exec_trim(t_token *token, t_token *last);
void			node_left(t_token *token, t_token *pivot);
void			free_pivot(t_token *pivot);
int				check_in_paranthesis(t_token *token, t_token *end);

t_token	*trim_paranthesis(t_token *token, t_token *end, t_token **out_end)
{
	t_token	*last;

	if (!token || !token->next)
		return (token);
	last = lstlast_before(token, end);
	if (token->token_type != TOKEN_PARENTHESIS_IN
		|| last->token_type != TOKEN_PARENTHESIS_OUT
		|| !check_in_paranthesis(token, end))
		return (token);
	*out_end = last;
	return (exec_trim(token, last));
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

static t_token	*exec_trim(t_token *token, t_token *last)
{
	if (token->next == last)
		return (NULL);
	return (token->next);
}

void	free_pivot(t_token *pivot)
{
	if (!pivot)
		return ;
	if (pivot->value)
		free(pivot->value);
	free(pivot);
}

int	check_in_paranthesis(t_token *token, t_token *end)
{
	int		count;
	t_token	*temp;

	if (!token || token->token_type != TOKEN_PARENTHESIS_IN)
		return (0);
	count = 0;
	temp = token;
	while (temp && temp != end)
	{
		if (temp->token_type == TOKEN_PARENTHESIS_IN)
			count++;
		else if (temp->token_type == TOKEN_PARENTHESIS_OUT)
			count--;
		if (count == 0 && temp->next != NULL && temp->next != end)
			return (0);
		temp = temp->next;
	}
	return (count == 0);
}
