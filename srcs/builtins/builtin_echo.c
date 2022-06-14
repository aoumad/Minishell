/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:12:36 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/14 15:28:38 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_echo(int argc __attribute((unused)), char **argv)
{
    int i;
    int n_flag;

    i = 0;
    n_flag = false;
    while (argv[i])
    {
        if (!ft_strcmp(argv[i], "-n"))
            n_flag = 1;
        i++;
    }
    while (argv[i])
    {
        ft_putstr_fd(argv[i], 1);
        if (argv[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (n_flag == 0)
        ft_putchar_fd('\n', 1);
    return (0);
}