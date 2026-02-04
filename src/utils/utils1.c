#include "../../include/minishell.h"

void	set_data(t_data *data, char **env)
{
	ft_bzero(data, sizeof(t_data));
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		ft_error("Error : Malloc of exec\n");
	ft_bzero(data->exec, sizeof(t_exec));
	data->envp = env;
}

void	ft_error(char *errorname)
{
	perror(errorname);
	exit (EXIT_FAILURE);
}

void	ft_freetab(char **tab)
{
	int i = 0;
	while(tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_node(t_ast *node)
{
	if (!node)
		return ;
	free_node(node->left);
	free_node(node->right);
	if (node->args)
		ft_freetab(node->args);
	if (node->redir)
	{
		while(node->redir)
		{
			free(node->redir->file);
			node->redir = node->redir->next;
		}
		free(node->redir);
	}
	free(node);
}
