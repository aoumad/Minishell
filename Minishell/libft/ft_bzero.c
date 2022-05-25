/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 02:51:28 by aoumad            #+#    #+#             */
/*   Updated: 2021/12/01 11:13:48 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cast_var;
	size_t			i;

	i = 0;
	cast_var = (unsigned char *)s;
	while (i < n)
		cast_var[i++] = 0;
}
