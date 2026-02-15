#include "../../include/minishell.h"

int	env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->val)
		{
			ft_printf("%s", tmp->key);
			write(1, "=", 1);
			ft_printf("%s\n", tmp->val);
		}
		tmp = tmp->next;
	}
	return (0);
}
