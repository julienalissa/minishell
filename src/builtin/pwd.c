/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pwd.c                                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:17:53 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:17:54 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}
