/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ast_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:13:10 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/11 12:29:16 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	creat_redir(t_token *temp_redir, t_ast **node, t_token *temp_file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return;
	ft_bzero(new, sizeof(t_redir));
	choise_redir(&new, temp_redir);
	if (new->redir_type == NODE_HEREDOC)
	{
		new->delimiter = ft_strdup(temp_file->value);
		if (temp_file->states == QUOTES || temp_file->states == DQUOTES)
			new->quote_hd = 1;
	}
	else
		new->file = ft_strdup(temp_file->value);
	new->next = NULL;
	if ((*node)->redir == NULL)
		(*node)->redir = new;
	else
		addback_redir(&(*node)->redir, new);
}

int	is_redir(t_token *token)
{
	if (token->token_type == TOKEN_APPEND || token->token_type == TOKEN_HEREDOC
		|| token->token_type == TOKEN_REDIR_IN
		|| token->token_type == TOKEN_REDIR_OUT)
		return (1);
	else
		return (0);
}

void	choise_redir(t_redir **redir, t_token *temp_redir)
{
	if (temp_redir->token_type == TOKEN_APPEND)
		(*redir)->redir_type = NODE_APPEND;
	else if (temp_redir->token_type == TOKEN_HEREDOC)
		(*redir)->redir_type = NODE_HEREDOC;
	else if (temp_redir->token_type == TOKEN_REDIR_IN)
		(*redir)->redir_type = NODE_REDIR_IN;
	else if (temp_redir->token_type == TOKEN_REDIR_OUT)
		(*redir)->redir_type = NODE_REDIR_OUT;
}

void	addback_redir(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

	if (!lst || !*lst)
	{
		*lst = new;
		return;
	}
	if (!lst && !new)
		return;
	temp = last_redir(*lst);
	if (temp)
		temp->next = new;
	else
		*lst = temp;
}

t_redir	*last_redir(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
