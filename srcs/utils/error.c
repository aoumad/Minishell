/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:39:12 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/02 16:36:51 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error(char *shell_name, char *s1, char *message)
{
	if (shell_name)
	{
		ft_putstr_fd(shell_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s1)
		ft_putstr_fd(s1, 2);
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (ERROR);
}

int	ft_error_malloc(char *shell_name, char *s1, char *message)
{
	if (shell_name)
	{
		ft_putstr_fd(shell_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s1)
		ft_putstr_fd(s1, 2);
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

void	ft_free_env(void)
{
	int	i;

	i = 0;
	while (g_data.g_env[i] != NULL)
	{
		free(g_data.g_env[i]);
		i++;
	}
	free(g_data.g_env);
}

void	free_cmd(t_list **head, t_command *cmd, char *buffer)
{
	deletelist(head);
	free_all(cmd);
	free(buffer);
}
