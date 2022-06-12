/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:47:12 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/12 18:54:59 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    execute_root(t_command *data, char **envp, t_list *list, char **argv)
{
    int status;
    int is_builtin_in;
    int i;
    int pid;
    int j;
    int nb_args;
    int fork_status;
    

    pid = -1;
    nb_args = 0;
    i = 0;
    j = 0;
    fork_status = 0;
    status = 0;
    while (j < data->num_cmd)
    {
        //=====================
        is_builtin_in = builtin_check(data[i].cmd[0]);
        // if (is_builtin_in != 0)
        // {
        //     if (nb_args < data[i].num_of_args || data)
        //         i++;
        // }
        if (data[i + 1].num_cmd != NULL || nb_args < data[i].num_of_args)
            pipe(data->pipe_fd);
        if (is_builtin_in == 0 || data[i + 1].num_cmd != 0)
        {
            fork_status = 1;
            pid = fork();
        }
        //=====================
        if (pid == 0 || is_builtin_in == FALSE || fork_status == 0)
        {
            envp = execute_process_builtin(data, i, envp);
            return (envp);
        }
        else
            close_pipex(*data, index);
    }
}

void    close_pipex(t_command *data, int index)
{
    if (index > 0)
        close(data[index - 1].pipe_fd[0]);
    if (index > 1)
        close(data[index - 2].pipe_fd(1));
    if (data[index + 1].num_cmd != NULL)
        close(data[index + 1].pipe_fd[1]);
    if (data[index + 1].num_cmd == NULL && index > 0)
    {
        dup2(data[index].fd_stdin, STDIN);
        dup2(data[index].fd_stdout, STDOUT);
        
    }
}

char    **execute_process_builtin(t_command *data, int index, char  **envp, char **argv)
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
        envp = ft_exec(data, envp, index, argv);
    return (envp);
}

char    **ft_exec(t_command *data, char **envp, int index, char **argv)
{
    int is_builtin_in;
    char *path;

    is_builtin_in = builtin_check(data[index].cmd[0]);
    if (is_builtin_in != 0)
    {
        g_builtins[index - 1].func(ft_wordcount(argv, " "), data->cmd);
        return (envp);
    }
    else
    {
        path = get_path(envp, data);
        if (path != NULL)
            execve(path, data[index].cmd, envp);
        free(path);
        return (envp);
    }
    return (envp);
}

// int exec_process(t_command *data, int index, char **envp)
// {
//     int pid;

//     pid = -1;
//     if (data[index].)
// }