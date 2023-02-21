/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_additional.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 23:31:11 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/06 21:09:38 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_2(char **argv, char *new, int i)
{
	int	status;

	status = EXIT_SUCCESS;
	if (check_arg(new) == false || error_symbol(new) == false)
	{
		ft_error("minishell", argv[i], "not a valid identifier");
		status = EXIT_FAILURE;
	}
	status = put_the_var(new);
	return (status);
}

char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	int		count;

	count = env_count(env);
	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < (count - 1))
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

void	exported_vars(void)
{
	char	**dup_env;
	int		i;
	int		count;

	count = env_count(g_data.g_env) + 1;
	dup_env = (char **)malloc((env_count(g_data.g_env) + 1) * sizeof(char *));
	if (dup_env == NULL)
		return ;
	if (g_data.g_env == NULL)
		return ;
	ft_memcpy(dup_env, g_data.g_env,
		(env_count(g_data.g_env) + 1) * sizeof(char *));
	dup_env[(env_count(g_data.g_env) + 1) * sizeof(char *) - 1] = 0;
	i = 0;
	dup_env = sort_env(dup_env);
	i = 0;
	while (dup_env[i])
	{
		g_data.g_env[i] = dup_env[i];
		i++;
	}
	g_data.g_env[i] = NULL;
	exported_vars_additional(dup_env);
}

void	exported_vars_additional(char **dup_env)
{
	int	i;

	i = 0;
	while (g_data.g_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(g_data.g_env[i], '=') == NULL)
		{
			ft_putendl_fd(g_data.g_env[i], 1);
			i++;
			continue ;
		}
		dup_env[i] = join_to_env(g_data.g_env[i]);
		ft_putstr_fd(dup_env[i], 1);
		ft_putendl_fd("\"", 1);
		i++;
	}
	i = 0;
	while (dup_env[i])
	{
		free(dup_env[i]);
		i++;
	}
	free(dup_env);
}

char	*join_to_env(char	*env)
{
	int		i;
	char	*tmp;
	char	*str;
	int		count;
	char	*quot;

	i = 0;
	count = ft_strlen(env);
	while (i < count)
	{
		if (env[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	str = ft_substr(env, 0, i);
	tmp = ft_strjoin_n(str, "\"");
	quot = ft_substr(env, i, (count - i));
	str = ft_strjoin_n(tmp, quot);
	free(quot);
	return (str);
}
