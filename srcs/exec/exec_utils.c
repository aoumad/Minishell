/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:34:15 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/12 16:22:18 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *get_path(char **envp,  t_command *data)
{
    char    **paths;
    char    *path;
    int     i;
    char    *part_path;

    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    paths = ft_split(envp[i] + 5, ":");
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, data->cmd[0]);
        free(part_path);
        if (access(path, F_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    ft_command_not_found(paths, data->cmd[0], data);
    return (0);
}

void ft_command_not_found(char **paths, char *cmd, t_command *data)
{
    int i;
    
    i = 0;
    while (paths[i++])
        free(paths[i]);
    free(paths);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found", 2);
    // i need to free the t_command to avoid leaks
    exit(EXIT_FAILURE);
}

int open_file(t_redirection *redirect, char **env)
{
    int fd;

    if (redirect->type == IN)
        fd = open(redirect->file, O_RDONLY);
    if (redirect->type == OUT)
        fd = open(redirect->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (redirect->type == APPEND)
        fd = open(redirect->file, O_WRONLY | O_APPEND | O_CREAT, 0664);
    // if (redirect->type == HEREDOC)
    //     fd = ft_heredoc() HEREDOC FUNCTION WITH INT TYPE, fd = ft_heredoc(...)
    if (fd < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        return (perror(redirect->file), -1); // Error!!!: No such file or directory
    }
    return (fd);
}