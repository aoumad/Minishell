/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:50:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/03 01:39:47 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(char *name)
{
	char	*env;

	env = search_env(name);
	if (env != 0)
		return (ft_strchr(env, '=') + 1);
	else
		return (NULL);
}

char	*search_env(char *name)
{
	int	len_name;
	int	i;

	if (name == NULL || g_data.g_env == NULL)
		return (NULL);
	if (ft_strchr(name, '=') != NULL)
		len_name = ft_strchr(name, '=') - name;
	else
		len_name = ft_strlen(name);
	i = 0;
	while (g_data.g_env[i])
	{
		if (!ft_strncmp(name, g_data.g_env[i], len_name))
			return (g_data.g_env[i]);
		i++;
	}
	return (NULL);
}

bool	check_var_is_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*ft_strchr_export(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char )c)
			return ((char *)s + 1);
		s++;
	}
	if ((char )c == 0)
		return ((char *)s + 1);
	return (NULL);
}

int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
