/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:24:31 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/03 15:59:05 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handl_herdoc(char *str)
{
	char	*new;
	int		leng;
	int		j;
	char	*tmp;

	j = -1;
	new = NULL;
	leng = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	while (++j < leng)
	{
		if (str[j] == dollar
			&& !cherche_symbol(str[j + 1], "\t!$%'() *\"+,-./:;<=>@[]^`{|}~"))
			new = check_dollar(&j, str, new, g_data.g_env);
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
	{
		if (str[i] == '\t' || str[i] == '\v' || str[i] == '\f'
			|| str[i] == ' ' || str[i] == '\r' || str[i] == '\n')
			return (0);
	}
	return (1);
}

void	heredoc_core(char *line, char *eof, int pipe_heredoc[2])
{
	int	rtn_value;

	rtn_value = 0;
	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
	rtn_value = pipe_heredoc[0];
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strcmp(eof, line))
		{
			free(line);
			break ;
		}
		heredoc_core_2(line, pipe_heredoc);
	}
	exit (0);
}

void	heredoc_core_2(char	*line, int pipe_heredoc[2])
{
	if (ft_strlen(line))
	{
		line = handl_herdoc(line);
		write(pipe_heredoc[1], line, ft_strlen(line));
	}
	write(pipe_heredoc[1], "\n", 1);
	free(line);
}

int	ft_heredoc(char *eof)
{
	char	*line;
	int		pipe_heredoc[2];
	int		pid;
	int		status;

	line = NULL;
	if (pipe(pipe_heredoc) != 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		heredoc_core(line, eof, pipe_heredoc);
	close(pipe_heredoc[1]);
	waitpid(-1, &status, 0);
	if (status == 2)
	{
		write(1, "\n", 1);
		g_data.g_status = 1;
		return (-1);
	}
	return (pipe_heredoc[0]);
}
