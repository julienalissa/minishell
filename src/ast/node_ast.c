#include "../../include/minishell.h"

void	creat_lst(t_token *token, t_data *data, t_list **args_lst);
void	creat_cmd_node(t_list *args_lst, t_ast **node);

t_ast	*creat_node(t_token	*token, t_data *data)
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
		if (temp->token_type == TOKEN_AND || temp->token_type == TOKEN_OR)
		{
			creat_operator(temp, &node);
			break ;
		}
		else if (is_redir(temp))
		{
			creat_redir(temp, &node, temp->next);
			temp = temp->next->next;
		}
		else if (temp->token_type == TOKEN_WORD)
		{
			creat_lst(temp, data, &args_lst);
			temp = temp->next;
		}
	}
	creat_cmd_node(args_lst, &node);
	return(node);
}

void	creat_lst(t_token *token, t_data *data, t_list **args_lst)
{
	t_list	*lst;
	if ((*args_lst) == NULL)
	{
		(*args_lst) = malloc(sizeof(t_list));
		if(ft_strchr(token->value, '*') && token->states == NORMAL)
			expand_asterisk(token->value, args_lst);
		else if (token->states != QUOTES && ft_strchr(token->value, '$'))
			expand_dollar(token->value, args_lst, data);
		else
			(*args_lst)->content = ft_strdup(token->value);
	}
	else
	{
		lst = malloc(sizeof(t_list));
		if(!lst)
			return ;
		if(ft_strchr(token->value, '*') && token->states == NORMAL)
			expand_asterisk(token->value, &lst);
		else if (token->states != QUOTES && ft_strchr(token->value, '$'))
			expand_dollar(token->value, &lst, data);
		else
			lst->content = ft_strdup(token->value);
		ft_lstadd_back(args_lst, lst);
	}
}

void	creat_cmd_node(t_list *args_lst, t_ast **node)
{
	t_list	*temp;
	int	size;
	int	i;

	if(!args_lst)
		return;
	i = 0;
	temp = args_lst;
	size = ft_lstsize(temp);
	(*node)->args = malloc(sizeof(char *) * size + 1);
	while(temp)
	{
		(*node)->args[i] = ft_strdup((char *)temp->content);
		i++;
		temp = temp->next;
	}
	(*node)->args[i] = NULL;
	(*node)->left = NULL;
	(*node)->right = NULL;
	// ft_lstclear args_lst
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
		return ;
	(*node)->args[0] = ft_strdup(temp->value);
	(*node)->args[1] = NULL;
}


