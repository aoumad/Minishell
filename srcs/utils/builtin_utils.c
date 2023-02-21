/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:41:08 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/06 21:29:54 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_to_env(char *str)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((env_count(g_data.g_env) + 2) * sizeof(char *));
	if (!new_env)
	{
		ft_error("minishell", NULL, strerror(ENOMEM));
		printf("\n");
		return (0);
	}
	i = 0;
	while (g_data.g_env[i])
	{
		new_env[i] = g_data.g_env[i];
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free(g_data.g_env);
	free (str);
	g_data.g_env = new_env;
	return (0);
}

int	remove_from_env(char *str)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(env_count(g_data.g_env) * sizeof(char *));
	if (new_env == NULL)
	{
		ft_error("minishell", NULL, strerror(ENOMEM));
		return (0);
	}
	i = 0;
	j = 0;
	while (g_data.g_env[i])
	{
		if (g_data.g_env[i] == str)
			i++;
		new_env[j++] = g_data.g_env[i++];
	}
	new_env[j] = NULL;
	free(g_data.g_env);
	free(str);
	g_data.g_env = new_env;
	return (0);
}

int	replace_str_env(char *old_str, char *new_str)
{
	int	i;

	if (g_data.g_env == NULL || old_str == NULL)
		return (ERROR);
	i = 0;
	while (g_data.g_env[i] && ft_strcmp(g_data.g_env[i], old_str))
		i++;
	if (ft_strcmp(g_data.g_env[i], old_str))
		return (ERROR);
	else if (check_replace(old_str, new_str) == true)
		g_data.g_env[i] = ft_strdup(new_str);
	else
		return (0);
	return (0);
}

bool	check_replace(char *old_str, char *new_str)
{
	if (ft_strchr(old_str, '=') && ft_strchr(new_str, '='))
		return (true);
	else if (!ft_strchr(old_str, '=') && ft_strchr(new_str, '='))
		return (true);
	else if (ft_strchr(old_str, '=') && !ft_strchr(new_str, '='))
		return (false);
	return (true);
}
