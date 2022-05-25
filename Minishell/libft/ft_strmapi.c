/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 22:55:56 by aoumad            #+#    #+#             */
/*   Updated: 2021/12/02 14:03:24 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*app;

	if (!s || !f)
		return (NULL);
	app = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!app)
		return (NULL);
	i = -1;
	while (s[++i])
		app[i] = f(i, s[i]);
	app[i] = 0;
	return (app);
}
