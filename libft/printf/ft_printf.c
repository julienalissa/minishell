/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:55:22 by ludebarn          #+#    #+#             */
/*   Updated: 2025/12/22 11:08:49 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_checkformat_printf(const char c, va_list *param)
{
	char	*ifint;
	int		count;

	count = 0;
	ifint = "diuxX";
	if (c == '%')
		count += ft_putchar_printf('%');
	else if (c == 'c')
		count += ft_putchar_printf(va_arg(*param, int));
	else if (c == 's')
		count += ft_putstr_printf(va_arg(*param, char *));
	else if (c == 'p')
		count += ft_putnbr_base_printf("0123456789abcdef",
				(unsigned long)va_arg(*param, void *), 16, c);
	else if (ft_strchr_printf(ifint, c))
		count += ft_putdigit_printf(c, param);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	va_list	param;
	int		count;

	i = 0;
	count = 0;
	va_start (param, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '.' || str[i] == 'f')
				count += float_format(str[i], &param, &i, str);
			else
				count += ft_checkformat_printf(str[i], &param);
		}
		else
			count += ft_putchar_printf(str[i]);
		i++;
	}
	va_end(param);
	return (count);
}

