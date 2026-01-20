#include "../../include/minishell.h"

void	lst_clear_env(t_env **lst)
{
	t_env *tmp;

	if (!lst)
		return;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->val);
		free(*lst);
		*lst = tmp;
	}
}