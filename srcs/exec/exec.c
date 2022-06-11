/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:47:12 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/10 19:06:25 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    execute_root(t_command *data, char **envp, t_list *list)
{
    int status;
    int is_builtin_in;
    int i;
    int pid;
    int nb_args;

    pid = -1;
    nb_args = 0;
    i = 0;
    status = 0;
    while (i < data->num_cmd)
    {
        is_builtin_in = builtin_check(data, list);
        if (nb_args < data[i].num_of_args || data)

        i++;
    }
}