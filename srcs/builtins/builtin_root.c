/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:15:39 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/12 16:45:20 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

int builtin_check(char  *str)
{
    int cmd_len;
    int is_builtin;
    int i;
    
    i = 0;
    is_builtin = 0;
    if (ft_strncmp(str, "NULL", 4) || ft_strncmp(str, "exit", 5))
        is_builtin = -1;
    while (g_builtins[i].name != NULL)
    {
        cmd_len = ft_strlen(g_builtins[i].name);
        if (str && !ft_strncmp(str, g_builtins[i].name, cmd_len + 1))
            is_builtin = i + 1; // avoid returning the value 0 since it's known for NULL in builtin_root func and not in the struct
        i++;
    }
    return (is_builtin);
}

void    builtin_root(char **argv, t_command *data)
{
    int   i;

    i = builtin_check(data[0].cmd[0]);
    if (i == -1)
        return (builtin_exit(split_count(argv), argv));
    if (i == 0)
        return (ERROR);
    return (g_builtins[i - 1].func(ft_wordcount(argv, " "), data->cmd));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
}

