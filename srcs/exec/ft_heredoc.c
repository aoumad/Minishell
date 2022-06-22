/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:24:31 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/22 17:00:37 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int delimiter_check(char *line, char *eof)
{
    int delim_len;
    
    delim_len = ft_strlen(line);
    if (!ft_strncmp(eof, line, delim_len) && line)
            return (0);
    return (1);
}

int    ft_heredoc(t_command *data, int index, char *eof)
{
    char    *line;
    int     rtn_value;
    int     pipe_heredoc[2];

    rtn_value = dup(STDOUT_FILENO);
    if (pipe(pipe_heredoc) != 0)
        return (0);
    if (data[index].redirect->next == NULL)
    {
        while (1)
        {
            line = readline("> ");
            if (line != NULL && !delimiter_check(line, eof))
                break;
            if (line == NULL)
                break;
            // if (line != NULL && line[0] = '$')
                // expander function
            write(pipe_heredoc[1], line, ft_strlen(line));
            write(pipe_heredoc[1], "\n", 1);
            free(line);
        }
        free(line);
        dup2(pipe_heredoc[0], STDIN_FILENO);
        close(pipe_heredoc[0]);
        close(pipe_heredoc[1]);
    }
    else 
        rtn_value = multiple_heredoc()
    return (rtn_value);
}