/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:14:44 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/21 14:01:23 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    execute_root(t_command *data, char **envp)
{
    int status;
    int i;
    int pid;
    int fd[2];
    char *path;
    int rtn_execve;

    rtn_execve = 0;
    i = 0;
    status = 0;
    pid = -1;
    ft_save_io(fd);
    while (i < data[0].num_cmds)
    {
        data[i].is_builtin_in = builtin_check(data[i].cmd[0]);
        data[i].pipe_fd[0] = STDIN_FILENO;
        data[i].pipe_fd[1] = STDOUT_FILENO;
        if (data[0].num_cmds > 1 && i != data[0].num_cmds - 1)
            pipe(data[i].pipe_fd);
        dup2(data[i].pipe_fd[0], STDIN_FILENO);
        dup2(data[i].pipe_fd[1], STDOUT_FILENO);
            
        if (data[i].is_builtin_in)
        {
            builtin_root(data[i].cmd);
            continue;
        }
        
        pid = fork();
        data[i].fork = 1;
        
        if (pid == 0)
        {
            close(data[i].pipe_fd[0]);
            close(data[i].pipe_fd[1]);
            path = get_path(envp, data, i);
            rtn_execve = execve(path, data[i].cmd, envp);
            exit(126);
        }
        if (i == data[0].num_cmds - 1)
            waitpid(pid, &status, 0);
        while (1)
        {
            if (waitpid(-1, 0, 0) == -1)
                break;
        }
        
        i++;
    }   
    ft_reset_io(fd);
}