/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:15:39 by aoumad            #+#    #+#             */
/*   Updated: 2022/05/25 08:59:13 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

static const struct s_builtin g_builtins[] = {
  {"cd", cd_builtin},
  /*{"pwd", pwd_builtin},
  {"echo", echo_builtin},
  {"env", env_builtin},
  {"unset", unset_builtin},
  {"export", export_builtin},*/
  {NULL, NULL},
};

int builtin_check(t_cmd *cmd)
{
    int is_builtin;

    is_builtin = 0;
    if (ft_strcmp() cmd->args[0] || !ft_strncmp(args[0], "exit", 4))
    {
        if ()
    }
    
}

void    builtin_root(char **argv, t_data *data, )
{
    int   i;

    i = builtin_check()
    
    i = 
}