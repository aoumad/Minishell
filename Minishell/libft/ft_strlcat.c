/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:26:37 by aoumad            #+#    #+#             */
/*   Updated: 2021/11/25 11:26:41 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	size_t			i;
	size_t			j;
	size_t			rtn;

	i = 0;
	j = 0;
	while (src[i])
		i++;
	if (!dest && !size)
		return (i);
	while (dest[j])
		j++;
	if (j <= size)
		rtn = i + j;
	else
		rtn = i + size;
	i = 0;
	while (src[i] && j + 1 < size)
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (rtn);
}
