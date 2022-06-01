/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:15:39 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/01 10:36:30 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

static void ft_quote_remove(t_cmd *cmd);

/*static const struct s_builtin   g_builtins[] = {
  {"cd", cd_builtin},
  /*{"pwd", pwd_builtin},
  {"echo", echo_builtin},
  {"env", env_builtin},
  {"unset", unset_builtin},
  {"export", export_builtin},
  {NULL, NULL},
  
};*/

static const struct s_builtins	g_builtins[] = 
{
	{"echo", builtin_echo},
    {"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"env", builtin_env},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{NULL, NULL},
};

int builtin_check(t_cmd *cmd)
{
    int cmd_len;
    int is_builtin;
    int i;
    
    i = 0;
    is_builtin = 0;
    if (ft_strncmp(cmd->args[0], "NULL", 4) || ft_strncmp(cmd->args[0], "exit", 5))
        is_builtin = -1;
    while (g_builtins[i].name != NULL && cmd->name != NULL)
    {
        cmd_len = ft_strlen(g_builtins[i].name);
        if (cmd->args[0] && !ft_strncmp(cmd->args[0], g_builtins[i].name, cmd_len + 1))
            is_builtin = i + 1; // avoid returning the value 0 since it's known for NULL in builtin_root func and not in the struct
        i++;
    }
    return (is_builtin);
}

void    builtin_root(char **argv, t_cmd *cmd)
{
    int   i;

    i = builtin_check(cmd);
    if (i == 0)
        return (ERROR);
    errno = 0;
    /*if (i == -1)
        let's think about it later */
    return (g_builtins[i - 1].func(ft_wordcount(argv, " "), cmd->args));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
}
