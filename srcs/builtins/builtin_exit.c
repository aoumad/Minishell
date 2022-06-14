/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:37:52 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/14 15:34:02 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static  int		ft_isspace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

static  long long  ft_atoi_exit(const char *str, int i, int *status_error)
{
    long    minus;
    long long   res;
    
    minus = 1;
    res = 0;
    if (str[i] && (str[i] == '+' || str[i] == '-'))
        if (str[i++] == '-')
            minus *= -1;
    while (str[i] && ft_isspace(str[i]))
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = (res * 10) + (str[i] - '0');
        if ((i >= 18))
            status_error = (int *)1;
    }
    return (res * minus);
}

static void    exit_numeric_error(char *arg)
{
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": numeric argument required", 2);
    g_status = 2;
}

static void    check_numeric(char *arg)
{
    int i;

    i = 0;
    if (arg[i] == '-' || arg[i] == '+')
        i++;
    while (arg[i])
    {
        if (!ft_isspace(arg[i]))
            if (arg[i] < 48 || arg[i] > 57)
                exit_numeric_error(arg);
        i++;
    }
}

int builtin_exit(int argc, char **argv)
{
    int         i;
    long long   rtn_atoi;
    int         status_error;
    
    
    g_status = 0;
    status_error = 0;
    i = 1;
    if (argc == 1)
        ft_putstr_fd("exit\n", STDERR_FILENO);
    check_numeric(argv[1]);
    while (argv[i])
        i++;
    if (i > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        g_status = 1;
    }
    else if (argc == 2)
    {
        rtn_atoi = ft_atoi_exit(argv[1], 0, &status_error);
        if (status_error == 1)
            exit_numeric_error(argv[1]);
        g_status = rtn_atoi % 256;
    }
    ft_putstr_fd("exit\n", STDERR_FILENO); // still didn't handle status return value
    return (0);
}