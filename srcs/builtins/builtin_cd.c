/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:25:11 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/01 16:01:35 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_cd(int argc __attribute((unused)), char **argv)
{
    int i;

    
}

char    *get_the_print_working_dir()
{
    char    *path[MAX_BUF];

    getcwd(path, MAX_BUF);
    if (path == NULL)
        return (ERROR);
    return (path);
}

