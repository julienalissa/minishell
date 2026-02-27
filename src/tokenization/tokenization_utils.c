/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   tokenization_utils.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:22:46 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:22:47 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	define_token(t_token *node);

t_token	*lstnew_token(char *tmp, t_states state)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = ft_strdup(tmp);
	node->states = state;
	define_token(node);
	node->next = NULL;
	return (node);
}

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst || !new)
		return ;
	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	temp = lstlast_token(*lst);
	temp->next = new;
}

t_token	*lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	define_token(t_token *node)
{
	if (!node || !node->value)
		return ;
	if (ft_strncmp(node->value, "<<", 2) == 0)
		node->token_type = TOKEN_HEREDOC;
	else if (ft_strncmp(node->value, ">>", 2) == 0)
		node->token_type = TOKEN_APPEND;
	else if (ft_strncmp(node->value, "&&", 2) == 0)
		node->token_type = TOKEN_AND;
	else if (ft_strncmp(node->value, "||", 2) == 0)
		node->token_type = TOKEN_OR;
	else if (ft_strncmp(node->value, "|", 1) == 0)
		node->token_type = TOKEN_PIPE;
	else if (ft_strncmp(node->value, "<", 1) == 0)
		node->token_type = TOKEN_REDIR_IN;
	else if (ft_strncmp(node->value, ">", 1) == 0)
		node->token_type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(node->value, "(", 1) == 0)
		node->token_type = TOKEN_PARENTHESIS_IN;
	else if (ft_strncmp(node->value, ")", 1) == 0)
		node->token_type = TOKEN_PARENTHESIS_OUT;
	else
		node->token_type = TOKEN_WORD;
}
