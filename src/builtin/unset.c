#include "../../include/minishell.h"

int	unset(char **args,t_data *data)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;

	i = 1;
	while (args[i])
	{
		if (data->env)
			tmp = data->env;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(tmp->key,args[i]) == 0)
			{
				if (prev)
					prev->next = tmp->next;
				else
					data->env = tmp->next;
				free(tmp->key);
				free(tmp->val);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
