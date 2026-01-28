#include "ast.h"

void	creat_redir(t_token	*temp_redir, t_ast **node, t_token *temp_file)
{
	t_redir	*new_node_redir;

	new_node_redir = NULL;
	if ((*node)->redir == NULL)
	{
		(*node)->redir = malloc(sizeof(t_redir));
		choise_redir(&(*node)->redir, temp_redir);
		(*node)->redir->file = ft_strdup(temp_file->value);
	}
	else
	{
		new_node_redir = malloc(sizeof(t_redir));
		choise_redir(&new_node_redir, temp_redir);
		new_node_redir->file = ft_strdup(temp_file->value);
		addback_redir(&(*node)->redir, new_node_redir);
	}
}

int	is_redir(t_token *token)
{
	if(token->token_type == TOKEN_APPEND || token->token_type == TOKEN_HEREDOC
		|| token->token_type == TOKEN_REDIR_IN || token->token_type == TOKEN_REDIR_OUT)
		return (1);
	else
		return(0);
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
		return ;
	}
	if (!lst && !new)
		return ;
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
