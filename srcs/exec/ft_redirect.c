/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:44:17 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/25 15:05:27 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_handler(t_command *data, int i)
{
	int index = i;
	t_redirection *red;
	int          c = 0, n = 0;
	
	red = data[i].redirect;
	while (red != NULL)
	{
		if (red->type == HEREDOC)
			c++;
		red = red->next;
	}
	red = data[i].redirect;
		while (red != NULL)
		{
			if (red->type == HEREDOC)
				n++;
			if (red && red->type == HEREDOC && n == c)
			{
				dup2(red->fd, STDIN_FILENO);
				close(red->fd);
				break ;
			}
			red = red->next;
		}
	//printf("the red is %s\n",red->file);
	while (data[i].redirect->next)
	  data[i].redirect = data[i].redirect->next;
	// pipe(data[i].redirect->redirect_fd);
	if (data[i].redirect->type == IN)
	{
		dup2(data[i].redirect->fd, STDIN_FILENO);
		close(data[i].redirect->fd);
	}
	if (data[i].redirect->type == OUT || data[i].redirect->type == APPEND)
	{
		dup2(data[i].redirect->fd, STDOUT_FILENO);
		close(data[i].redirect->fd);
	}
	if (data[index].redirect->fd == HEREDOC)
	{
		dup2(data[i].redirect->fd, STDOUT_FILENO);
		close(data[i].redirect->fd);
	}
}