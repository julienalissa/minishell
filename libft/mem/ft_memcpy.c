/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:24:42 by lucasdebarn       #+#    #+#             */
/*   Updated: 2025/12/22 11:08:12 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*realdst;
	const unsigned char	*realsrc;

	i = 0;
	if ((!dst && !src) && n)
		return (NULL);
	realdst = (unsigned char *)dst;
	realsrc = (const unsigned char *)src;
	while (i < n)
	{
		realdst[i] = realsrc[i];
		i++;
	}
	return (dst);
}
