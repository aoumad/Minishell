/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:30:42 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/18 18:36:49 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **copy_env(char **envp)
{
    int     i;
    char    **rtn_env;
    int     index;
    
    i = -1;
    index = 0;
    while (envp[++i])
        index++;
    rtn_env = malloc(sizeof(char *) * (index + 1));
    i = 0;
    while (i < index)
    {
        rtn_env[i] = ft_strdup(envp[i]);
        i++;
    }
    rtn_env[i] = NULL;
    return (rtn_env);
}

int main(int argc, char **argv, char **envp)
{
    t_command *data;
	char    *line;
    int status;
    int i;
    int j;
    int c;
    (void)argc;
	
    i = 0;
    status = 0;
	g_env = NULL;
    g_exit_value = 0;
    line = NULL;
    g_env = copy_env(envp);
    if (!g_env[i])
    {
        ft_free_env(&g_env);
        return (ft_error("minishell", NULL, strerror(ENOMEM)));
    }
    i = 1;
    j = 1;
    while (argv[i])
    {
        if (ft_strchr(argv[i], '|'))
            j++;
        i++;
    }
    c = 1;
    i = 1;
    j = 0;
    data = malloc(sizeof(t_command) * j);
    while (argv[i])
    {
        if (ft_strchr(argv[i], '|'))
        {
            data[j].cmd = malloc(sizeof(char) * c);
            i = 0;
            j++;
        }
        c++;  
        i++;
    }
    i = 1;
    while (argv[i])
    {
        data[0].cmd[i - 1] = argv[i];
        i++;
    }
    data[0].cmd[i - 1] = NULL;
    g_env = execute_root(data, envp, i);
    free(data);
    while (--i)
        free(data[0].cmd[i]);
    free(&data[0].cmd);
    return (0);
}