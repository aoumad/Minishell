/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:24:31 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/28 11:42:21 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handl_herdoc(char *str)
{
	char	*new;
	int		leng;
	int		j;
	int		start;
	char	*tmp;

	j = -1;
	new = NULL;
	leng = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	while (++j < leng)
	{
		if (str[j] == dollar
			&& !cherche_symbol(str[j + 1], "\t!$%'() *\"+,-./:;<=>?@[]^`{|}~"))
			new = check_dollar(&j, str, new, g_env);
		else
		{
			tmp[0] = str[j];
			new = ft_strjoin_n(new, tmp);
		}
	}
	free(tmp);
	free(str);
	return (new);
}

int	line_empty_no_n(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\t' && str[i] == '\v' && str[i] == '\f'
			&& str[i] == ' ' && str[i] == '\r' )
			return (0);
	return (1);
}

void	heredoc_core(char *line, char *eof, int pipe_heredoc[2], int rtn_value)
{
	signal(SIGINT, SIG_DFL);
	rtn_value = pipe_heredoc[0];
	line = ft_strdup("");
	while (ft_strcmp(eof, line))
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strcmp(eof, line))
			break ;
		if (!line_empty_no_n(line))
		{
			free(line);
			write(pipe_heredoc[1], "\n", 1);
			continue ;
		}
		else if (ft_strlen(line))
		{
			line = handl_herdoc(line);
			write(pipe_heredoc[1], line, ft_strlen(line));
			write(pipe_heredoc[1], "\n", 1);
		}
		free(line);
	}
	exit (0);
}

int	ft_heredoc(t_command *data, int index, char *eof)
{
	char	*line;
	int		rtn_value;
	int		pipe_heredoc[2];
	int		pid;
	int		status;

	if (pipe(pipe_heredoc) != 0)
		return (rtn_value);
	pid = fork();
	if (pid < 0)
		return (-1);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		heredoc_core(line, eof, pipe_heredoc, rtn_value);
	close(pipe_heredoc[1]);
	waitpid(-1, &status, 0);
	if (status == 2)
	{
		g_status = 130;
		return (-1);
	}
	return (pipe_heredoc[0]);
}
