/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:22:30 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/16 16:02:35 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lstclear_token(t_token **lst)
{
	t_token	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		lstdel_token(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	lstdel_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}
