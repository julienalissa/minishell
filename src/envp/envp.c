#include "../../include/minishell.h"

char	*define_key(char *env);
char	*define_value(char *env);

void	creat_env(t_data *data)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*env_tmp;

	i = 0;
	while (data->envp[i])
	{
		key = define_key(data->envp[i]);
		value = define_value(data->envp[i]);
		env_tmp = lstnew_env(key, value);
		if (!env_tmp)
		{
			free(value);
			free(key);
			lstclear_env(data);
		}
		lstadd_back_env(&data->env, env_tmp);
		i++;
	}
}

void	creat_envp(t_data *data)
{
	int		count;

	if (!data || !data->env)
		return ;
	count = count_env(data->env);
	data->envp = alloc_envp(data->env, count);
}
