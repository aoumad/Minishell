/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:17:15 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/02 14:46:57 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(int argc __attribute((unused)), char **argv)
{
	int	i;

	if (path_no_found(argv) == 1)
		return (0);
	if (g_data.g_env == NULL)
	{
		ft_error("minishell", "env", "environ not set");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (g_data.g_env[i])
	{
		if (ft_strchr(g_data.g_env[i], '='))
			ft_putendl_fd(g_data.g_env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	path_no_found(char **argv)
{
	int	check;
	int	i;

	i = 0;
	check = 0;
	while (g_data.g_env[i] && ft_strnstr(g_data.g_env[i], "PATH", 4) == NULL)
	{
		if (ft_strnstr(g_data.g_env[i], "PATH", 4) == NULL
			&& g_data.g_env[i + 1] == NULL)
		{
			ft_error("minishell", argv[0],
				": No such file or directory");
			check = 1;
		}
		i++;
	}
	return (check);
}
