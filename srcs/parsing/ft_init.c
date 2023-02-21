/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:33:11 by snouae            #+#    #+#             */
/*   Updated: 2022/07/03 14:40:34 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**rtn_env;
	int		index;

	i = -1;
	index = 0;
	while (envp[++i])
		index++;
	rtn_env = malloc(sizeof(char *) * (index + 1));
	if (!rtn_env)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	i = 0;
	while (i < index)
	{
		rtn_env[i] = ft_strdup(envp[i]);
		i++;
	}
	rtn_env[i] = NULL;
	return (rtn_env);
}

int	skip_redirect(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '>' || str[i] == '<')
		i = 2;
	while (cherche_symbol(str[i], " \t\n\v\f\r"))
		i++;
	return (i);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_data.g_status = 1;
	}
}

int	ft_check(t_list **head)
{
	t_list	*current;

	current = *head;
	while (current != NULL)
	{
		if (!check_cases(&current))
			return (0);
		current = current->next;
	}
	return (1);
}
