/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 20:19:21 by llachgar          #+#    #+#             */
/*   Updated: 2018/10/11 14:09:41 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr(int n)
{
	char	a;
	long	n1;
	int		i;

	n1 = n;
	if (n1 < 0)
	{
		write(1, "-", 1);
		n1 *= -1;
	}
	if (n == 0)
		write(1, "0", 1);
	if (n1 != 0)
	{
		i = n1 / 10;
		if (i != 0)
			ft_putnbr(i);
		a = (n1 % 10) + '0';
		write(1, &a, 1);
	}
}
