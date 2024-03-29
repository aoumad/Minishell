/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_additional.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:02:38 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/03 00:59:09 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_core(t_command *data, int i, char **envp)
{
	int		pid;
	int		fd[2];

	pid = -1;
	ft_save_io(fd);
	dup_io(data, i);
	if (data[i].redirect)
		redirect_handler(data, i);
	if (data[i].is_builtin_in && data[i].redirect == NULL)
	{
		g_data.g_status = builtin_root(data[i++].cmd);
		ft_reset_io(fd);
		return (99);
	}
	pid = fork();
	if (pid < 0)
		ft_error_malloc("minishell", NULL, "Fork Failed");
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		execute_child(data, i, envp);
	ft_reset_io(fd);
	return (pid);
}

void	execute_child(t_command *data, int i, char **envp)
{
	int		rtn_execve;
	char	*path;
	int		check;

	check = 0;
	rtn_execve = 0;
	add_to_child(data, i);
	if (!ft_strncmp(data[i].cmd[0], "./", 2))
	{
		check = open_dir_handler(data, i);
		path = data[i].cmd[0];
	}
	else
		path = get_path(envp, data, i);
	if (check == 0)
	{
		rtn_execve = execve(path, data[i].cmd, envp);
		if (rtn_execve == -1)
			g_data.g_status = exit_status(data, i);
	}
	exit(g_data.g_status);
}

void	add_to_child(t_command *data, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (data[i].prev)
		close(data[i].prev[1]);
	if (data[i].next)
		close(data[i].next[0]);
}

int	open_dir_handler(t_command *data, int i)
{
	int	check;

	check = 0;
	if (opendir(data[i].cmd[0]) != NULL)
	{
		check = 1;
		ft_error("minishell", data[i].cmd[0], " is a directory");
		g_data.g_status = 126;
	}
	return (check);
}

int	exit_status(t_command *data, int i)
{
	if (errno == 13)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data[i].cmd[0], 2);
		perror(" ");
		return (126);
	}
	else
		return (127);
}
