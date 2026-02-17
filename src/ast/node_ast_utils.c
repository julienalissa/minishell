#include "../../include/minishell.h"

t_token	*check_op_redir(t_token *temp, t_ast **node,
	t_data *data, t_list **args_lst)
{
	if (temp->token_type == TOKEN_AND || temp->token_type == TOKEN_OR)
	{
		creat_operator(temp, node);
		return (NULL);
	}
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
			return (NULL);
		}
	}
	return (temp);
}

t_token	*check_list(t_token *temp, t_data *data, t_list **args_lst)
{
	while (temp && temp->token_type == TOKEN_WORD)
	{
		creat_lst(temp, data, args_lst);
		temp = temp->next;
	}
	return (temp);
}

t_ast	*creat_node(t_token *token, t_data *data)
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
	while (temp && temp->token_type != TOKEN_PIPE)
	{
		temp = check_op_redir(temp, &node, data, &args_lst);
		if (!temp)
			return (NULL);
		if (temp && temp->token_type == TOKEN_WORD)
			temp = check_list(temp, data, &args_lst);
	}
	creat_cmd_node(args_lst, &node);
	return (node);
}
