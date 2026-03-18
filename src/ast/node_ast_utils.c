/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:15:27 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/18 09:12:47 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*parenthesis_error(t_token *temp, t_data *data, t_ast *node,
					t_list *args_lst);
static t_token	*check_op_redir(t_token *temp, t_ast **node, t_data *data,
					t_list **args_lst);
static t_token	*check_list(t_token *temp, t_data *data, t_list **args_lst);

t_ast	*creat_node(t_token *token, t_token *end, t_data *data)
{
	t_ast	*node;
	t_token	*temp;
	t_list	*args_lst;

	if (!token)
		return (NULL);
	args_lst = NULL;
	temp = token;
	node = malloc(sizeof(t_ast));
	ft_bzero(node, sizeof(t_ast));
	while (temp && temp->token_type != TOKEN_PIPE && temp != end)
	{
		temp = check_op_redir(temp, &node, data, &args_lst);
		if (!node)
			return (NULL);
		if (!temp)
			break ;
		if (temp && temp->token_type == TOKEN_WORD)
			temp = check_list(temp, data, &args_lst);
		else if (temp && (temp->token_type == TOKEN_PARENTHESIS_IN
				|| temp->token_type == TOKEN_PARENTHESIS_OUT))
			return (parenthesis_error(temp, data, node, args_lst));
	}
	creat_cmd_node(args_lst, &node);
	return (node);
}

static t_token	*check_op_redir(t_token *temp, t_ast **node, t_data *data,
		t_list **args_lst)
{
	if (temp->token_type == TOKEN_AND || temp->token_type == TOKEN_OR)
		return (creat_operator(temp, node), NULL);
	else if (is_redir(temp))
	{
		if (temp->next && temp->next->token_type == TOKEN_WORD)
		{
			creat_redir(temp, node, temp->next);
			return (temp->next->next);
		}
		else
		{
			ft_printf("-bash: syntax error near unexpected token\n");
			data->last_exit_code = 2;
			if ((*node)->args)
				ft_freetab((*node)->args);
			if (*args_lst)
				ft_lstclear(args_lst, free);
			free(*node);
			*node = NULL;
			return (NULL);
		}
	}
	return (temp);
}

static t_token	*check_list(t_token *temp, t_data *data, t_list **args_lst)
{
	while (temp && temp->token_type == TOKEN_WORD)
	{
		creat_lst(temp, data, args_lst);
		temp = temp->next;
	}
	return (temp);
}

static t_ast	*parenthesis_error(t_token *temp, t_data *data, t_ast *node,
		t_list *args_lst)
{
	ft_printf("-bash: syntax error near unexpected token `%s'\n", temp->value);
	data->last_exit_code = 2;
	if (node->args)
		ft_freetab(node->args);
	if (args_lst)
		ft_lstclear(&args_lst, free);
	free(node);
	return (NULL);
}
