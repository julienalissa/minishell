#include "../../include/minishell.h"

// POUR AFFICHER L'ARBRE DANS LE TERMINAL (FAIT AVEC IA MAIS POUR AVOIR UN RENDU VISUEL )

void	print_node_content(t_ast *node)
{
	t_redir	*tmp;

	if (!node)
		return ;
	if (node->op_type == NODE_PIPE)
		printf("( PIPE )");
	else if (node->op_type == NODE_AND)
		printf("( AND )");
	else if (node->op_type == NODE_OR)
		printf("( OR )");
	else if (node->args && node->args[0])
	{
		printf("[%s]", node->args[0]);
		if (node->args[1])
			printf(" ...");
		tmp = node->redir;
		while (tmp)
		{
			if (tmp->redir_type == NODE_REDIR_IN)
				printf(" < %s", tmp->file);
			else if (tmp->redir_type == NODE_REDIR_OUT)
				printf(" > %s", tmp->file);
			else if (tmp->redir_type == NODE_APPEND)
				printf(" >> %s", tmp->file);
			else if (tmp->redir_type == NODE_HEREDOC)
				printf(" << %s", tmp->file);
			tmp = tmp->next;
		}
		printf("]");
	}
}

void	print_tree_visual(t_ast *node, int space, char branch)
{
	int	i;

	if (node == NULL)
		return ;
	space += 10;
	print_tree_visual(node->right, space, '/');
	printf("\n");
	i = 10;
	while (i < space)
	{
		printf(" ");
		i++;
	}
	if (branch == '/')
		printf("/-- ");
	else if (branch == '\\')
		printf("\\-- ");
	print_node_content(node);
	printf("\n");
	print_tree_visual(node->left, space, '\\');
}
