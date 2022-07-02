/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:14:44 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/02 13:03:30 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	fd_generator(t_command *data, int index)
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

void	dup_io(t_command *data, int i)
{
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
}

void	execute_root(t_command *data, char **envp)
{
	int	i;
	int	pid;

	i = 0;
	pid = -1;
	while (i < data[0].num_cmds)
		fd_generator(data, i++);
	i = 0;
	while (i < data[0].num_cmds)
	{
		data[i].is_builtin_in = builtin_check(data[i].cmd[0]);
		if (data[i].next)
			pipe(data[i].next);
		if (data[i].exec == 0)
			pid = execute_core(data, i, envp);
	  	else
	   {
		   if (data[i].prev)
		   		close(data[i].prev[1]);
			if (data[i].next)
				close(data[i].next[1]);
	   }
		i++;
	}
	status_generator(data, i, pid);
}

void	status_generator(t_command *data, int i, int pid)
{
	if (i == data[0].num_cmds)
	waitpid(pid, &g_data.g_status, 0);
	while (1)
	{
		if (waitpid(-1, 0, 0) == -1)
			break;
	}
	if (g_data.g_status == 3)
	{
		printf("Quit: 3\n");
		g_data.g_status = 131;
	}
	else if(g_data.g_status == 2)
		g_data.g_status = 130;
	else if (g_data.g_status == 126 || g_data.g_status == 127)
		return ;
	else
		g_data.g_status = WEXITSTATUS(g_data.g_status);
}