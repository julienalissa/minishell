/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:24:33 by lucasdebarn       #+#    #+#             */
/*   Updated: 2025/12/22 11:08:04 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*reals1;
	const unsigned char	*reals2;

	i = 0;
	reals1 = (const unsigned char *)s1;
	reals2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (reals1[i] != reals2[i])
			return (reals1[i] - reals2[i]);
		i++;
	}
	return (0);
}
