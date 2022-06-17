/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:47:12 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/16 18:27:45 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **execute_root(t_command *data, char **envp) //, t_list *list need it later
{
    int status;
    int is_builtin_in;
    int i;
    int pid;
    int nb_args;
    int fork_status;
    
    pid = -1;
    nb_args = 0;
    i = 0;
    fork_status = 0;
    status = 0;
    int j = 0;
    while (data[i].num_cmds > j)
    {
        //=====================
        is_builtin_in = builtin_check(data[i].cmd[0]);
        // if (is_builtin_in != 0)
        // {
        //     if (nb_args < data[i].num_of_args || data)
        //         i++;
        // }
        /*if (data[i + 1].num_cmd != 0)
            pipe(data->pipe_fd);
        if (is_builtin_in == false || data[i + 1].num_cmd != 0)
        {
            fork_status = 1;
            pid = fork();
        }
        //=====================
        if (pid == 0 || is_builtin_in == false || fork_status == 0)
        {
            envp = execute_process_builtin(data, i, envp);
        }
        else if (is_builtin_in != 0)
        {*/
        builtin_root(data[i].cmd);
        // }
        // else
        //     close_fd(data, i, list);
        i++;
        j++;
    }
    /*i = 0;
    while (data[i].num_cmd != 0)
    {
        waitpid(-1, &status, 0);
        if (WIFEXITED(status))
            g_exit_value = WEXITSTATUS(status);
        i++;
    }*/
    return (envp);
}

/*void    close_fd(t_command *data, int index, t_list *list)
{
    if (index > 0)
        close(data[index - 1].pipe_fd[0]);
    if (data[index + 1].num_cmd != 0)
        close(data[index + 1].pipe_fd[1]);
    if (data[index + 1].num_cmd == 0 && index > 0)
    {
        if (list->type == IN)
            dup2(data[index].redirect->fd, STDIN_FILENO);
        if (list->type == OUT)
            dup2(data[index].redirect->fd, STDOUT_FILENO);
        if (data[index].pipe_fd[1] != 0)    
            close (data[index].pipe_fd[1]);
        if (data[index].pipe_fd[0] != 0)
            close (data[index].pipe_fd[0]);
    }
}*/

/*char    **execute_process_builtin(t_command *data, int index, char  **envp)
{
    if ((index > 0) && data[index + 1].num_cmd)
    {
        dup2(data[index].pipe_fd[0], 0);
        close(data[index].pipe_fd[0]);
    }
    if (data[index + 1].num_cmd != 0)
    {
        dup2(data[index].pipe_fd[1], 1);
        close(data[index].pipe_fd[0]);
    }
    // if (data[index].redirect->file)
    //     i need to call a redirection execution function
    else
        envp = ft_exec(data, envp, index);
    return (envp);
}

char    **ft_exec(t_command *data, char **envp, int index)
{
    char *path;
        path = get_path(envp, data);
        if (path != NULL)
            execve(path, data[index].cmd, envp);
        free(path);
        return (envp);
    return (envp);
}*/