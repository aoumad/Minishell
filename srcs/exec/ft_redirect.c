/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:44:17 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/03 02:47:04 by snouae           ###   ########.fr       */
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
		if ((red && red->type == HEREDOC && n == c))
		{
			dup2(red->fd, STDIN_FILENO);
			close(red->fd);
			break ;
		}
		red = red->next;
	}
}

void	redirect_out_append(t_command *data, int i, int c, int n)
{
	t_redirection	*red;

	red = data[i].redirect;
	while (red != NULL)
	{
		if (red->type == OUT || red->type == APPEND)
			c++;
		red = red->next;
	}
	red = data[i].redirect;
	while (red != NULL)
	{
		if (red->type == OUT || red->type == APPEND)
			n++;
		if (((red && red->type == 2) || (red && red->type == 4)) && n == c)
		{
			dup2(red->fd, STDOUT_FILENO);
			close(red->fd);
			break ;
		}
		red = red->next;
	}
}

void	redirect_handler(t_command *data, int i)
{
	int				index;
	int				c;
	int				n;
	t_redirection	*head;

	c = 0;
	n = 0;
	index = i;
	read_handler(data, i, c, n);
	head = data[i].redirect;
	redirect_in_handler(data, i, c, n);
	while (head->next)
		head = head->next;
	if (head->fd == HEREDOC)
	{
		dup2(head->fd, STDOUT_FILENO);
		close(head->fd);
	}
	redirect_out_append(data, i, c, n);
}

void	redirect_in_handler(t_command *data, int i, int c, int n)
{
	t_redirection	*red;

	red = data[i].redirect;
	while (red != NULL)
	{
		if (red->type == IN)
			c++;
		red = red->next;
	}
	red = data[i].redirect;
	while (red != NULL)
	{
		if (red->type == IN)
			n++;
		if ((red && red->type == IN && n == c))
		{
			dup2(red->fd, STDIN_FILENO);
			close(red->fd);
			break ;
		}
		red = red->next;
	}
}
