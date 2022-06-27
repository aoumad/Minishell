/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_riderct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:28:44 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/27 10:28:46 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void open_files(t_command *cmd, int leng)
{
	int i;
	t_redirection *head;

	i = 0;
	while (i < leng)
	{
		if(cmd[i].redirect)
		{
			head = cmd[i].redirect;
			while (head != NULL)
			{
				if (head->type == IN)
					head->fd = open(head->file, O_RDONLY);
				else if (head->type == OUT)
					head->fd = open(head->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				else if (head->type == APPEND)
					head->fd = open(head->file, O_WRONLY | O_APPEND | O_CREAT, 0664);
				 if (head->type == HEREDOC)
					head->fd = ft_heredoc(cmd, i, head->file);
				if (head->fd < 0)
					perror("minishell: ");
				head = head->next;
			}
		}
		i++;
	}
}