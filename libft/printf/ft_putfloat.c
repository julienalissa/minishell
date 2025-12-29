/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:29:49 by ludebarn          #+#    #+#             */
/*   Updated: 2025/12/22 11:08:59 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int float_format(char c, va_list *param, size_t *i, const char *str)
{
	int precision;
	int count;

	count = 0;
	precision = 0;
	if (c == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
			precision = (precision * 10) + str[*i++] - '0';
		count += get_float_printf(precision, va_arg(*param, double));
	}
	else if (c == 'f')
			count += get_float_printf(6, va_arg(*param, double));
	return (count);
}

int	get_float_printf(int precision, double value)
{
	int		count;
	char	*str;

	count = 0;
	str = NULL;
	str = ft_ftoa (value, precision);
	if (!str)
		return (0);
	count += ft_putstr_printf(str);
	free(str);
	return (count);
}
