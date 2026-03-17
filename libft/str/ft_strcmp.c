/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strcmp.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:28:07 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:28:08 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
