/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_split_clear.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:27:38 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:27:39 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_clear(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
