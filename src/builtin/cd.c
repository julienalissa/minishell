/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   cd.c                                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:16:41 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:16:42 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(char **args)
{
	char	*path;
	int		ret;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_printf("home is unset\n");
			return (1);
		}
	}
	else
		path = args[1];
	ret = chdir(path);
	if (ret != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
