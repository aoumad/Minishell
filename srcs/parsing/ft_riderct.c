/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_riderct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:44:18 by snouae            #+#    #+#             */
/*   Updated: 2022/07/03 14:59:40 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_error_files(t_redirection *head, t_command **cmd)
{
	if (head->fd < 0 && head->status && head->type != APPEND)
	{
		ft_error("minishell", "$", " ambiguous redirect");
		(*cmd)->exec = 1;
		return (1);
	}
	else if (head->fd < 0 && !head->status && head->type != HEREDOC)
	{
		printf("the file is %d\n", head->fd);
		ft_error("minishell", head->file, ": No such file or directory");
		(*cmd)->exec = 1;
		g_data.g_status = 1;
		return (1);
	}
	else if (head->fd < 0 && head->type == HEREDOC)
	{
		g_data.st_err = 1;
		(*cmd)->exec = 1;
		return (1);
	}
	return (0);
}

void	create_files(t_redirection **head)
{
	if ((*head)->type == IN)
		(*head)->fd = open((*head)->file, O_RDONLY);
	else if ((*head)->type == OUT)
		(*head)->fd = open((*head)->file,
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if ((*head)->type == APPEND)
		(*head)->fd = open((*head)->file,
				O_WRONLY | O_APPEND | O_CREAT, 0664);
}

void	open_all_heredoc(t_command *cmd, int leng)
{
	int				i;
	t_redirection	*head;

	i = -1;
	while (++i < leng)
	{
		if (cmd[i].redirect)
		{
			head = cmd[i].redirect;
			while (head != NULL)
			{
				if (head->type == HEREDOC)
				{
					head->fd = ft_heredoc(head->file);
					check_error_files(head, &cmd);
				}
				head = head->next;
			}
		}
	}
}

void	open_files(t_command *cmd, int leng)
{
	int				i;
	t_redirection	*head;

	i = 0;
	open_all_heredoc(cmd, leng);
	while (i < leng)
	{
		if (cmd[i].redirect)
		{
			head = cmd[i].redirect;
			while (head != NULL)
			{
				create_files(&head);
				if (check_error_files(head, &cmd))
					break ;
				head = head->next;
			}
		}
		i++;
	}
}
