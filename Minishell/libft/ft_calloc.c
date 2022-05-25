/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 02:51:26 by aoumad            #+#    #+#             */
/*   Updated: 2021/11/29 15:29:51 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*add;
	size_t			len;

	len = count * size;
	add = (unsigned char *)malloc(len);
	if (!add)
		return (NULL);
	ft_bzero(add, len);
	return (add);
}
