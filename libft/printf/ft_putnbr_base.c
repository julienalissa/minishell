/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:51:23 by lucasdebarn       #+#    #+#             */
/*   Updated: 2025/12/22 11:09:03 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putdigit_printf(const char c, va_list *param)
{
	int		count;
	long	nb;

	count = 0;
	nb = 0;
	if (c == 'd' || c == 'i')
	{
		nb = va_arg(*param, int);
		if (nb < 0)
		{
			count += ft_putchar_printf('-');
			nb *= -1;
		}
		count += ft_putnbr_base_printf("0123456789", nb, 10, c);
	}
	else if (c == 'u')
		count += ft_putnbr_base_printf("0123456789", (long)va_arg(*param,
					unsigned), 10, c);
	else if (c == 'x')
		count += ft_putnbr_base_printf("0123456789abcdef", (long)va_arg(*param,
					unsigned), 16, c);
	else if (c == 'X')
		count += ft_putnbr_base_printf("0123456789ABCDEF", (long)va_arg(*param,
					unsigned), 16, c);
	return (count);
}

void	put_base_printf(unsigned long nbr, char *base, unsigned int lenbase)
{
	if (nbr >= lenbase)
	{
		put_base_printf((nbr / lenbase), base, lenbase);
		put_base_printf((nbr % lenbase), base, lenbase);
	}
	else
		write(1, &base[nbr], 1);
}

int	ft_countlen_printf(unsigned long nb, unsigned int lenbase)
{
	int	count;

	count = 1;
	if (nb == 0)
		return (1);
	while (nb >= lenbase)
	{
		count++;
		nb /= lenbase;
	}
	return (count);
}

int	ft_putnbr_base_printf(char *base, unsigned long n, unsigned int lenbase,
		const char c)
{
	int		count;
	long	nb;

	count = 0;
	if (c == 'p')
	{
		if (!n)
			return (ft_putstr_printf("(nil)"));
		else
			count += ft_putstr_printf("0x");
	}
	nb = n;
	count += ft_countlen_printf(nb, lenbase);
	put_base_printf(nb, base, lenbase);
	return (count);
}
