/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:47:12 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/18 18:34:27 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **execute_command(t_command *data, char **envp, int index)
{
    char    *path;
    int     pid;
    
    path = get_path(envp, data, index);
    pid = -1;
    if (data[index].redirect->type != NONE)
    {
        pid = fork();
        if (pid == 0)
            execve(path, data[index].cmd, envp);
        else
            waitpid(-1, 0, 0);
    }
    else
        execve(path, data[index].cmd, envp);
    return (envp);
}

char    **exec_1(t_command *data, int index, char **envp)
{
    if (index > 0 && data[index].num_cmds != 0)
    {
        dup2(data[index].pipe_fd[0], STDIN_FILENO);
        close(data[index].pipe_fd[0]);
        close(data[index].pipe_fd[1]);
    }
    if (data[index + 1].num_cmds != 0)
    {
        dup2(data[index].pipe_fd[1], STDOUT_FILENO);
        close(data[index].pipe_fd[0]);
        close(data[index].pipe_fd[1]);
    }
    // if (data[index].redirect->file)
    //     redirect_execution(data, envp);
    else
        envp = execute_command(data, envp, index);
    return (envp);
}

char    **execute_root(t_command *data, char **envp, int index) //, t_list *list need it later
{
    int status;
    int i;
    int j;
    int pid;
    int nb_args;

    j = index;
    i = index; // ch7al mne data[index] 3ndi
    status = 0;
    nb_args = 0;
    pid = -1;
    while(--i)
    {
        pid  = ft_pipe_built(data, pid, j);
        if (pid == 0 || (data[j].is_builtin_in != 0 && data[j].fork == 0 && index > 0))
        {
            envp = exec_1(data, index, envp);
            return (envp);
        }
        else
        {
            close(data[index].pipe_fd[0]);
            close(data[index].pipe_fd[1]);
        }
        index++;
    }
    while (--j)
    {
        	waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_exit_value = WEXITSTATUS(status);
    }
    return (envp);
}

int ft_pipe_built(t_command *data, int pid, int index)
{
    int i;

    i = data[index].num_cmds;
    data[index].is_builtin_in = builtin_check(data[index].cmd[0]);
    if (data[index + 1].num_cmds != 0)
        pipe(data[index].pipe_fd);
    if (data[index].is_builtin_in == 0 && index > 0)
    {
        data[index].fork = 1; // nchofo blano
        pid = fork();
    }
    return (pid);
}