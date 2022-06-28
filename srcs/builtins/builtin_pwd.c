/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 09:50:51 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/28 10:28:29 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(int argc __attribute((unused)),
	char **argv __attribute((unused)))
{
	char	buf[MAX_BUF];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		return (0);
	}
	else
	{
		ft_error("minishell", "pwd", strerror(ENOMEM));
		return (EXIT_FAILURE);
	}
}
