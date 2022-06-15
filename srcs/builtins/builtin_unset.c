/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:38:49 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/15 16:07:13 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_unset(int argc __attribute((unused)), char **argv)
{
    int i;
    int j;
    int status;

    i = 0;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j] && check_var_is_char(argv[i][j]))
            j++;
        if (argv[i][j] != '\0' || argv[i][0] == '\0')
        {
            ft_error("minishell", "unset", "not a valid identifier"); 
            status = EXIT_FAILURE;
        }
        else
            unset_the_var(argv[i]);
        i++;
    }
    return (status);
}

