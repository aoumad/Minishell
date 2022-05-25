/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:32:01 by aoumad            #+#    #+#             */
/*   Updated: 2021/12/01 11:45:26 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isin(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

static int	get_last_index(char const *s1, char const *set)
{
	int	len;

	len = ft_strlen(s1);
	while (--len >= 0)
		if (!ft_isin(set, s1[len]))
			break ;
	return (len);
}

static int	get_first_index(char const *s1, char const *set)
{
	int	i;

	i = -1;
	while (s1[++i])
		if (!ft_isin(set, s1[i]))
			break ;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s_trimed;
	int		first;
	int		last;
	int		j;

	if (!s1 || !set)
		return (NULL);
	first = get_first_index(s1, set);
	last = get_last_index(s1, set);
	if (first > last)
	{
		s_trimed = (char *)malloc(sizeof(char));
		if (!s_trimed)
			return (NULL);
		s_trimed[0] = 0;
		return (s_trimed);
	}
	else
		s_trimed = (char *)malloc(sizeof(char) * (last - first + 2));
	if (!s_trimed)
		return (NULL);
	j = 0;
	ft_strlcpy(s_trimed, s1 + first, last - first + 2);
	return (s_trimed);
}
