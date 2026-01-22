#include "../../include/minishell.h"

void	expand_asterisk(char *name, t_list **lst);
void	creat_lst(t_token *token, t_data *data, t_list **args_lst);
void	expand_dollar(char *name, t_list **lst, t_data *data);
int		check_file(char *name, char *file);

t_ast	*creat_node(t_token	*token, t_data *data)
{
	t_ast	*node;
	t_token	*temp;
	t_list	*args_lst;

	temp = token;
	args_lst = NULL;
	if (temp->token_type == TOKEN_WORD)
		creat_lst(token, data, &args_lst);
	while (1)
	{
		printf("%s\n", (char *)args_lst->content);
		args_lst = args_lst->next;
		if (args_lst->next == NULL)
			break ;
	}
	// TODO : vérifier cas spéciaux pour l'expand '*', remplir t_ast avec la liste créer et regarder les redirections pour mettre dans structure spécial
	// assigné les autres opérateur, free t_list créer pour les tokens WORD, assigner tout pour pouvoir free t_token
	// Faire test, ensuite passer a l'éxecution
	printf("%s\n", (char *)args_lst->content);
	exit(1);
}

void	creat_lst(t_token *token, t_data *data, t_list **args_lst)
{
	t_list	*lst;

	while(token && token->token_type == TOKEN_WORD)
	{
		lst = malloc(sizeof(t_list));
		if(!lst)
			return ;
		lst->content = NULL;
		lst->next = NULL;
		if(ft_strchr(token->value, '*'))
			expand_asterisk(token->value, &lst);
		else if (token->states != QUOTES && ft_strchr(token->value, '$'))
			expand_dollar(token->value, &lst, data);
		else
			lst->content = ft_strdup(token->value);
		ft_lstadd_back(args_lst, lst);
		token = token->next;
	}
}
