#include "../../include/minishell.h"

void	expand_dollar(char *name, t_list **lst, t_data *data)
{
	int	len;
	t_env	*env_temp;

	env_temp = data->env;
	len = ft_strlen(name);
	while(env_temp)
	{
		if (ft_strncmp(env_temp->key, name + 1, len) == 0)
		{
			(*lst)->content = ft_strdup(env_temp->val);
			return ;
		}
		env_temp = env_temp->next;
	}
	(*lst)->content = ft_strdup("");
}


int	check_file(char *name, char *file)
{
	if (*name == '\0' && *file == '\0')
		return(1);
	else if (*name == *file && *name != '*')
		return(check_file(name + 1, file +1));
	else if (*name == '*')
		return (check_file(name + 1, file)
			|| (*file && check_file(name, file + 1)));
	return (0);
}

void	creat_asterisk(t_list **current, t_list	**lst, char *namefile, int *flag)
{
	if (*flag == 0)
	{
		(*current)->content = ft_strdup(namefile);
		*flag = 1;
	}
	else
	{
		(*current) = malloc(sizeof(t_list));
		if(!current)
			return ;
		(*current)->content = ft_strdup(namefile);
		(*current)->next = NULL;
		ft_lstadd_back(lst, (*current));
	}
}
void	expand_asterisk(char *name, t_list **lst)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_list			*current;
	int				flag;

	flag = 0;
	current = *lst;
	dirp = NULL;
	if (!ft_strchr (name, '/'))
		dirp = opendir(".");
	if(!dirp)
	{
		current->content = ft_strdup(name);
		return ;
	}
	while((dp = readdir(dirp)) != NULL)
	{
		if ((name[0] == '.' || dp->d_name[0] != '.')
			&& check_file(name, dp->d_name))
			creat_asterisk(&current, lst, dp->d_name, &flag);
	}
	closedir(dirp);
	if (flag == 0)
		current->content = ft_strdup(name);
}
