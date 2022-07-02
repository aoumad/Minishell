/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:37:52 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/02 16:51:51 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	long long	ft_atoi_exit11(char *str, int i, int *status_error)
{
	int			j;
	long		neg;
	long long	sum;

	neg = 1;
	sum = 0;
	j = 0;
	i = atoi_sup(str, &neg);
	while (str[i] >= '0' && str[i] <= '9' && ++j)
	{
		sum = (sum * 10) + (str[i] - 48);
		if (((i == 19 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 20 && neg == -1) && (str[i] == '9')))
			*status_error = 1;
		i++;
	}
	while (str[i++])
		j++;
	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
		*status_error = 1;
	return (sum * neg);
}

static	void	exit_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_data.g_status = 255;
	exit (g_data.g_status);
}

void	check_numeric(char *arg, int *rtn_numeric)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] != '\f' && arg[i] != '\t' && arg[i] != '\r'
			&& arg[i] != '\v' && arg[i] != ' ')
		{
			if (arg[i] < 48 || arg[i] > 57)
			{
				exit_numeric_error(arg);
				*rtn_numeric = 1;
				break ;
			}
		}
		i++;
	}
}

int	builtin_exit(int argc, char **argv)
{
	int			i;
	long long	rtn_atoi;
	int			status_error;
	int			rtn_numeric;

	g_data.g_status = 0;
	rtn_numeric = 0;
	status_error = 0;
	i = exit_core(argc, argv, rtn_numeric);
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_data.g_status = 1;
	}
	else
	{
		rtn_atoi = ft_atoi_exit11(argv[1], 0, &status_error);
		if (status_error == 1)
			exit_numeric_error(argv[1]);
		g_data.g_status = rtn_atoi % 256;
	}
	if (status_error != 1 || rtn_numeric == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(g_data.g_status);
	return (0);
}
