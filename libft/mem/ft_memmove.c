/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:18:15 by lucasdebarn       #+#    #+#             */
/*   Updated: 2025/12/22 11:08:26 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*realdst;
	const unsigned char	*realsrc;

	i = 0;
	if ((!dst && !src) || dst == src || n == 0)
		return (dst);
	realdst = (unsigned char *)dst;
	realsrc = (const unsigned char *)src;
	if (realdst < realsrc)
	{
		i = 0;
		while (i < n)
		{
			realdst[i] = realsrc[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
			realdst[i] = realsrc[i];
	}
	return (dst);
}
