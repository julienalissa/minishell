/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:38:32 by ludebarn          #+#    #+#             */
/*   Updated: 2025/12/22 11:04:05 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// choise number after comma
static char	*float_temp(double fpart, int fnb)
{
	int		i;
	char	*temp;
	char	*res;

	i = 0;
	temp = malloc(sizeof(char) * fnb + 1);
	if (!temp)
		return (NULL);
	while (i < fnb)
	{
		fpart *= 10;
		temp[i] = ((int)fpart % 10) + '0';
		i++;
	}
	temp[fnb] = '\0';
	res = ft_strjoin(".", temp);
	free(temp);
	return (res);
}

static char	*ft_result(double fpart, int ipart, int fnb)
{
	char	*itemp;
	char	*ftemp;
	char	*result;

	itemp = ft_itoa(ipart);
	ftemp = float_temp(fpart, fnb);
	result = ft_strjoin(itemp, ftemp);
	free(ftemp);
	free(itemp);
	return (result);
}

char	*ft_ftoa(double n, int fnb)
{
	double	fpart;
	int		ipart;
	char	*ret;

	ipart = (int)n;
	fpart = n - ipart;
	if (fpart < 0)
		fpart *= -1;
	ret = ft_result(fpart, ipart, fnb);
	return (ret);
}
