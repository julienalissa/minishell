/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:12:15 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/16 15:12:57 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*exec_trim(t_token *token, t_token *last);
void			node_left(t_token *token, t_token *pivot);
void			free_pivot(t_token *pivot);
int				check_in_paranthesis(t_token *token);

t_token	*trim_paranthesis(t_token *token)
{
	t_token	*last;

	if (!token || !token->next)
		return (token);
	last = lstlast_token(token);
	if (token->token_type != TOKEN_PARENTHESIS_IN
		|| last->token_type != TOKEN_PARENTHESIS_OUT
		|| !check_in_paranthesis(token))
		return (token);
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
	t_token	*start;
	t_token	*temp;

	if (token->next == last)
	{
		token->next = NULL;
		lstdel_token(token);
		lstdel_token(last);
		return (NULL);
	}
	start = token->next;
	token->next = NULL;
	lstdel_token(token);
	temp = start;
	while (temp->next != last)
		temp = temp->next;
	temp->next = NULL;
	lstdel_token(last);
	return (trim_paranthesis(start));
}

void	free_pivot(t_token *pivot)
{
	if (!pivot)
		return ;
	if (pivot->value)
		free(pivot->value);
	free(pivot);
}

int	check_in_paranthesis(t_token *token)
{
	int		count;
	t_token	*temp;

	if (!token || token->token_type != TOKEN_PARENTHESIS_IN)
		return (0);
	count = 0;
	temp = token;
	while (temp)
	{
		if (temp->token_type == TOKEN_PARENTHESIS_IN)
			count++;
		else if (temp->token_type == TOKEN_PARENTHESIS_OUT)
			count--;
		if (count == 0 && temp->next != NULL)
			return (0);
		temp = temp->next;
	}
	return (count == 0);
}
