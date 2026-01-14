#include "../../include/minishell.h"

char	*define_key(char *env);
void	creat_env(t_data *data);

void	creat_env(t_data *data)
{
	int	i;
	char *key;
	char *value;
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
			lstclear_env(&data);
		}
		lstadd_back_env(&data->env, env_tmp);
		i++;
	}
}

char	*define_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	while(env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	if(!key)
		return (NULL);
	return(key);
}

char	*define_value(char *env)
{
	unsigned int	start;
	char			*value;
	int				i;

	i = 0;
	while (env[i] != '=')
		i++;
	start = i + 1;
	while(env[i++]);
	value = ft_substr(env, start, i);
	if(!value)
		return (NULL);
	return(value);
}

void	creat_env(t_data *data)
{
	int	i;
	char *key;
	char *value;
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
			lstclear_env(&data);
		}
		lstadd_back_env(&data->env, env_tmp);
		i++;
	}
}
