/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:29:51 by aoumad            #+#    #+#             */
/*   Updated: 2021/11/25 11:29:55 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	i;

	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[j] && j < len)
	{
		if (haystack[j] == needle[0])
		{
			i = 0;
			while (haystack[j + i] == needle[i]
				&& haystack[j + i]
				&& j + i < len)
				i++;
			if (j + i > len)
				return (NULL);
			if (!needle[i])
				return ((char *)(haystack + j));
		}
		j++;
	}
	return (NULL);
}	
