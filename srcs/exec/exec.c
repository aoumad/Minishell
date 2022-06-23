/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:14:44 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/23 19:55:41 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    fd_generator(t_command *data, int index)
{
    if (index == 0)
    {
        data[0].prev = NULL;
        data[0].next = NULL;
        if (data[0].num_cmds > 1)
            data[0].next = data[0].pipe;
    }
    else if (index == data[0].num_cmds - 1)
    {
        data[index].prev = data[index - 1].pipe;
        data[index].next = NULL;
    }
    else
    {
        data[index].prev = data[index - 1].pipe;
        data[index].next = data[index].pipe;
    }
}

void    execute_root(t_command *data, char **envp)
{
    int status;
    int i;
    int pid;
    int fd[2];
    char *path;
    int rtn_execve;

    rtn_execve = 0;
    status = 0;
    pid = -1;
    i = 0;
    while (i < data[0].num_cmds)
        fd_generator(data, i++);
    i = 0;
    while (i < data[0].num_cmds)
    {
        //if (data[i].redirect == NULL)
            data[i].is_builtin_in = builtin_check(data[i].cmd[0]);
        if (data[i].next)
            pipe(data[i].next);
        ft_save_io(fd);
        if (data[i].prev)
        {
            dup2(data[i].prev[0], STDIN_FILENO);
            close(data[i].prev[0]);
        }
        if (data[i].next)
        {
            dup2(data[i].next[1], STDOUT_FILENO);
            close(data[i].next[1]);
        }
        if (data[i].redirect)
        {
            // t_redirection   *head;
            // while (head->next)
            //     head = head->next;
            // pipe(data[i].redirect->redirect_fd);
            if (data[i].redirect->type == IN || data[i].redirect->type == HEREDOC)
            {
                dup2(data[i].redirect->fd, STDIN_FILENO);
                close(data[i].redirect->fd);
            }
            if (data[i].redirect->type == OUT || data[i].redirect->type == APPEND || 
                data[i].redirect->type == HEREDOC)
            {
                dup2(data[i].redirect->fd, STDOUT_FILENO);
                close(data[i].redirect->fd);
            }
        }
        if (data[i].is_builtin_in  && data[i].redirect == NULL)
        {
            builtin_root(data[i++].cmd);
            ft_reset_io(fd);
            // if (i == data[0].num_cmds - 1)
            //     waitpid(pid, &status, 0);
            // while (1)
            // {
            //     if (waitpid(-1, 0, 0) == -1)
            //         break;
            // }
            continue;
        }
        pid = fork();
        if (pid == 0)
        {
            if (data[i].prev)
                close(data[i].prev[1]);
            if (data[i].next)
                close(data[i].next[0]);
            if (!ft_strncmp(data[i].cmd[0], "./", 2))
            {
                rtn_execve = execve(data[i].cmd[0], data[i].cmd, envp);
                if (rtn_execve == -1)
                    ft_error("minishell", data[i].cmd[0], ": No such file or directory\n");
            }
            else
            {
                path = get_path(envp, data, i);
                rtn_execve = execve(path, data[i].cmd, envp);
            }
            exit(126);
        }

        ft_reset_io(fd);
        // if (i == data[0].num_cmds - 1)
        //     waitpid(pid, &status, 0);
        //                         printf("hello again\n");
        // while (1)
        // {
        //     if (waitpid(-1, 0, 0) == -1)
        //         break;
        // }
        i++;
    }   
     while (1)
        {
            if (waitpid(-1, 0, 0) == -1)
                break;
        }
}