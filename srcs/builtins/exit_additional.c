/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_additional.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:11:26 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/02 16:11:42 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_core(int argc, char **argv, int rtn_numeric)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit (0);
	}
	if (argv[1] != NULL)
		check_numeric(argv[1], &rtn_numeric);
	while (argv[i])
		i++;
	return (i);
}

int	atoi_sup(char *str, long *neg)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if ((str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			*neg *= -1;
	while (str[i] && (str[i] == '0'))
		i++;
	return (i);
}
