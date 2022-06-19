/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:13:03 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/15 13:15:01 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	freememory(char **mem)
{
	int	i;

	i = 0;
	while (mem[i])
		free(mem[i++]);
	free(mem);
}

int	wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	ft_wordcount(char const *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	**fill(char **split, char const *s, char c)
{
	int	k;
	int	i;
	int	len;

	k = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			len = wordlen(s + i, c);
			split[k] = ft_substr(s, i, len);
			if (!split[k++])
			{
				freememory(split);
				return (NULL);
			}
			i += len;
		}
	}
	split[k] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!split)
		return (NULL);
	return (fill(split, s, c));
}