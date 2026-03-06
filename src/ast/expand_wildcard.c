/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:12:48 by jualissa          #+#    #+#             */
/*   Updated: 2026/03/05 17:07:05 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	creat_asterisk(t_list **current, t_list **lst, char *namefile,
				int *flag);
static int	check_file(char *name, char *file);

void	expand_asterisk(char *name, t_list **lst)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_list			*current;
	int				flag;

	flag = 0;
	current = *lst;
	dirp = NULL;
	if (!ft_strchr(name, '/'))
		dirp = opendir(".");
	if (!dirp)
	{
		current->content = ft_strdup(name);
		return ;
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		if ((name[0] == '.' || dp->d_name[0] != '.') && check_file(name,
				dp->d_name))
			creat_asterisk(&current, lst, dp->d_name, &flag);
	}
	closedir(dirp);
	if (flag == 0)
		current->content = ft_strdup(name);
}

static int	check_file(char *name, char *file)
{
	if (*name == '\0' && *file == '\0')
		return (1);
	else if (*name == *file && *name != '*')
		return (check_file(name + 1, file + 1));
	else if (*name == '*')
		return (check_file(name + 1, file) || (*file && check_file(name, file
					+ 1)));
	return (0);
}

static void	creat_asterisk(t_list **current, t_list **lst, char *namefile,
		int *flag)
{
	if (*flag == 0)
	{
		(*current)->content = ft_strdup(namefile);
		*flag = 1;
	}
	else
	{
		*current = malloc(sizeof(t_list));
		if (!*current)
			return ;
		(*current)->content = ft_strdup(namefile);
		(*current)->next = NULL;
		ft_lstadd_back(lst, (*current));
	}
}
