/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:44:17 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/01 14:26:08 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_handler(t_command *data, int i, int c, int n)
{
	t_redirection	*red;

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
}

void	redirect_handler(t_command *data, int i)
{
	int	index;
	int	c;
	int	n;
	t_redirection *head;

	c = 0;
	n = 0;
	index = i;
	read_handler(data, i, c, n);
	head = data[i].redirect;
	while (head->type == IN && head->next)
	{
		if (head->next->type == IN)
			head = head->next;
		else
			break ;
	}
	if (head->type == IN)
	{
		dup2(head->fd, STDIN_FILENO);
		close(head->fd);
	}
	while (head->next)
		head = head->next;
	if (head->type == OUT || head->type == APPEND)
	{
		dup2(head->fd, STDOUT_FILENO);
		close(head->fd);
	}
	if (head->fd == HEREDOC)
	{
		dup2(head->fd, STDOUT_FILENO);
		close(head->fd);
	}
}
