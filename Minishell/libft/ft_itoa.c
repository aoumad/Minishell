/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 02:54:06 by aoumad            #+#    #+#             */
/*   Updated: 2021/12/01 11:14:36 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int n)
{
	int				l;
	unsigned int	nb;

	l = 1;
	if (n < 0)
	{
		l++;
		nb = -n;
	}
	else
		nb = n;
	while (nb >= 10)
	{
		nb /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char			*num;
	unsigned int	nb;
	int				l;

	l = len(n);
	num = (char *)malloc(sizeof(char) * (l + 1));
	if (!num)
		return (NULL);
	num[l] = 0;
	num[0] = '-';
	l--;
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (nb >= 10)
	{
		num[l--] = nb % 10 + 48;
		nb /= 10;
	}
	num[l] = nb % 10 + 48;
	return (num);
}
