/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:18:29 by snouae            #+#    #+#             */
/*   Updated: 2022/07/03 14:46:30 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_error(t_list **head, char *buffer)
{
	if (!ft_check(head))
	{
		printf("minishell: syntax error !\n");
		g_data.g_status = 258;
		free(buffer);
		deletelist(head);
		return (1);
	}
	return (0);
}

int	ft_pars_execute(t_list **head, t_command *cmd, char *buffer)
{
	if (ft_strlen(buffer))
	{
		add_history (buffer);
		*head = ft_lexer(buffer);
		if (check_error(head, buffer))
			return (0);
		cmd = ft_parser(head);
		open_files(cmd, cmd[0].num_cmds);
		if (g_data.st_err)
		{
			free_cmd(head, cmd, buffer);
			return (0);
		}
		execute_root(cmd, g_data.g_env);
	}
	free_cmd(head, cmd, buffer);
	return (1);
}

void	ft_promt(char **buffer)
{
	g_data.st_err = 0;
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	rl_on_new_line();
	*buffer = readline("\033[1mminishell$> \033[m");
}

int	ft_init(t_list **head, t_command *cmd, char *buffer)
{
	if (line_empty(buffer))
	{
		free(buffer);
		return (0);
	}
	if (!ft_pars_execute(head, cmd, buffer))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_list		*head;
	char		*buffer;
	t_command	*cmd;

	(void)ac;
	(void)av;
	cmd = NULL;
	g_data.g_env = copy_env(envp);
	while (1)
	{
		ft_promt(&buffer);
		if (!buffer)
		{
			write(1, "exit", 4);
			break ;
		}
		ft_init(&head, cmd, buffer);
	}
	ft_free_env();
	return (0);
}
