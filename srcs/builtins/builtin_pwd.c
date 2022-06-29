/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 09:50:51 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/29 01:36:58 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rm_case()
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], "PWD", 3))
			printf("%s\n", g_env[i] + 4);
		i++;
	}
}

void	print_pwd()
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
	}
}

int	builtin_pwd(int argc __attribute((unused)),
	char **argv __attribute((unused)))
{
	int status;
	
	status = 0;
	if (!getcwd(NULL, 0))
	{
		status = 1;
		rm_case();
	}
	if (status == 0)
	{
		print_pwd();
	}
	return (status);
}
