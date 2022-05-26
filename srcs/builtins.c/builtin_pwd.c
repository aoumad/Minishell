/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 09:50:51 by aoumad            #+#    #+#             */
/*   Updated: 2022/05/26 17:51:02 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_pwd(int argc __attribute((unused)), 
    char **argv __attribute((unused)))
{
    char buf[PATH_MAX];

    if (getcwd(buf, sizeof(buf))); // getcwd returns null if path ain't found
    {
        ft_putendl_fd(buf, STDOUT_FILENO);
        return (0);
    }
    else
    {
        //it should print an error message for me
        return (EXIT_FAILURE);        
    }
}