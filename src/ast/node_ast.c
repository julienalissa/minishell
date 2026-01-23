#include "../../include/minishell.h"

void	creat_operator(t_token *temp, t_ast **node);
void	creat_lst(t_token *token, t_data *data, t_list **args_lst);
void	creat_cmd_node(t_token **token, t_list *args_lst, t_ast **node);

t_ast	*creat_node(t_token	*token, t_data *data)
{
	t_ast	*node;
	t_token	*temp;
	t_list	*args_lst;

	if (!token)
		return (NULL);
	temp = token;
	args_lst = NULL;
	while (temp)
	{
		if (temp->token_type == TOKEN_AND || temp->token_type == TOKEN_OR
			|| temp->token_type == TOKEN_PIPE)
			creat_operator(temp, &node);
		else if (temp->token_type == TOKEN_WORD)
		{
			creat_lst(temp, data, &args_lst);
			creat_cmd_node(&temp, args_lst, &node);
		}
		// else if (token->token_type == TOKEN_APPEND || token->token_type == TOKEN_HEREDOC
		// 	|| token->token_type == TOKEN_REDIR_IN || token->token_type == TOKEN_REDIR_OUT)
		// 	creat_redir(&temp, &node);
		temp = temp->next;
	}
	for (int i = 0; node->args[i] != NULL; i++)
		printf("%s\n", node->args[i]);
	// TODO : vérifier cas spéciaux pour l'expand '*', remplir t_ast avec la liste créer et regarder les redirections pour mettre dans structure spécial
	// assigné les autres opérateur, free t_list créer pour les tokens WORD, assigner tout pour pouvoir free t_token
	// Faire test, ensuite passer a l'éxecution
	node->left = NULL;
	node->right = NULL;
	exit(1);
}

void	creat_lst(t_token *token, t_data *data, t_list **args_lst)
{
	t_list	*lst;

	while(token)
	{
		lst = malloc(sizeof(t_list));
		if(!lst)
			return ;
		if (token->token_type == TOKEN_WORD)
		{
			lst->content = NULL;
			lst->next = NULL;
			if(ft_strchr(token->value, '*') && token->states == NORMAL)
				expand_asterisk(token->value, &lst);
			else if (token->states != QUOTES && ft_strchr(token->value, '$'))
				expand_dollar(token->value, &lst, data);
			else
				lst->content = ft_strdup(token->value);
		}
		ft_lstadd_back(args_lst, lst);
		token = token->next;
	}
}

void	creat_cmd_node(t_token **token, t_list *args_lst, t_ast **node)
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
	// ft_lstclear args_lst
}

void	creat_operator(t_token *temp, t_ast **node)
{
	(*node)->args = malloc(sizeof(char *) * 2);
	if (temp->token_type == TOKEN_AND)
		(*node)->op_type == NODE_AND;
	else if (temp->token_type == TOKEN_OR)
		(*node)->op_type == NODE_OR;
	else if (temp->token_type == TOKEN_PIPE)
		(*node)->op_type == NODE_PIPE;
	(*node)->args[0] = ft_strdup(temp->value);
	(*node)->args[1] = NULL;
	(*node)->redir = NULL;
}
