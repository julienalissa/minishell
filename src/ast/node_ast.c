/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   node_ast.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:13:01 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:13:02 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	creat_lst(t_token *token, t_data *data, t_list **args_lst);
void	creat_cmd_node(t_list *args_lst, t_ast **node);

void	add_new_token(t_token *token, t_data *data, t_list **lst)
{
	if (ft_strchr(token->value, '*') && token->states == NORMAL)
		expand_asterisk(token->value, lst);
	else if (token->states != QUOTES && ft_strchr(token->value, '$'))
		expand_dollar(token->value, lst, data);
	else
		(*lst)->content = ft_strdup(token->value);
}

void	creat_lst(t_token *token, t_data *data, t_list **args_lst)
{
	t_list	*lst;

	if (*args_lst == NULL)
	{
		*args_lst = malloc(sizeof(t_list));
		if (!*args_lst)
			return;
		(*args_lst)->next = NULL;
		add_new_token(token, data, args_lst);
	}
	else
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			return;
		lst->next = NULL;
		add_new_token(token, data, &lst);
		ft_lstadd_back(args_lst, lst);
	}
}

void	check_arg(t_list *args_lst, t_ast *node)
{
	t_list	*temp;
	int		i;
	int		size;

	size = ft_lstsize(args_lst);
	node->args = malloc(sizeof(char *) * (size + 1));
	if (!node->args)
		return;
	temp = args_lst;
	i = 0;
	while (temp)
	{
		node->args[i] = ft_strdup((char *)temp->content);
		i++;
		temp = temp->next;
	}
	node->args[i] = NULL;
}

void	creat_cmd_node(t_list *args_lst, t_ast **node)
{
	if (args_lst)
		check_arg(args_lst, *node);
	else
	{
		(*node)->args = malloc(sizeof(char *));
		if (!(*node)->args)
			return;
		(*node)->args[0] = NULL;
	}
	ft_lstclear(&args_lst, free);
	(*node)->left = NULL;
	(*node)->right = NULL;
}

void	creat_operator(t_token *temp, t_ast **node)
{
	(*node)->args = malloc(sizeof(char *) * 2);
	if (temp->token_type == TOKEN_AND)
		(*node)->op_type = NODE_AND;
	else if (temp->token_type == TOKEN_OR)
		(*node)->op_type = NODE_OR;
	else if (temp->token_type == TOKEN_PIPE)
		(*node)->op_type = NODE_PIPE;
	else
		return;
	(*node)->args[0] = ft_strdup(temp->value);
	(*node)->args[1] = NULL;
}
