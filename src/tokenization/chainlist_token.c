#include "../include/minishell.h"

void	define_token(t_token *node);
t_token	*lstlast_token(t_token *lst);

t_token	*lstnew_token(char *tmp, t_data *data)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = ft_strdup(tmp);
	node->states = data->flag_states;
	define_token(node);
	node->next = NULL;
	return (node);
}

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	if (!*lst && !new)
		return ;
	temp = lstlast_token(*lst);
	if (temp)
		temp->next = new;
	else
		*lst = temp;
}

t_token	*lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void define_token(t_token *node)
{
	if (ft_strncmp(node->value, "|", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_PIPE;
	else if (ft_strncmp(node->value, "<", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_REDIR_IN;
	else if (ft_strncmp(node->value, ">", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(node->value, "<<", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_HEREDOC;
	else if (ft_strncmp(node->value, ">>", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_APPEND;
	else if (ft_strncmp(node->value, "&&", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_AND;
	else if (ft_strncmp(node->value, "||", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_OR;
	else if (ft_strncmp(node->value, "(", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_PARENTHESIS_IN;
	else if (ft_strncmp(node->value, ")", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_PARENTHESIS_OUT;
	else
		node->token_type = TOKEN_WORD;
}
