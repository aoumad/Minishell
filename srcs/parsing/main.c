/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:18:29 by snouae            #+#    #+#             */
/*   Updated: 2022/06/25 20:48:59 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char    **copy_env(char **envp)
{
	int     i;
	char    **rtn_env;
	int     index;
	
	i = -1;
	index = 0;
	while (envp[++i])
		index++;
	rtn_env = malloc(sizeof(char *) * (index + 1));
	i = 0;
	while (i < index)
	{
		rtn_env[i] = ft_strdup(envp[i]);
		i++;
	}
	rtn_env[i] = NULL;
	return (rtn_env);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

void handler(int sig)
{
	if (sig ==  SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int line_empty(char *str)
{
	int i = -1;

	while (str[++i])
		if (str[i] != '\t'&& str[i] != '\v' && str[i] != '\f' &&
		str[i] != '\n' && str[i] != ' ' && str[i] != '\r' )
			return (0);
	return (1);
}
int main(int ac, char **av, char **envp)
{
	int test;
	t_list *head;
	char *buffer;
	t_command *cmd;


	cmd = NULL;
	(void)ac;
	(void)av;
	//env_init(envp);
	 g_env = copy_env(envp);
	if (!g_env)
	{
		ft_free_env(&g_env);
		return (ft_error("minishell", NULL, strerror(ENOMEM)));
	}
	//g_st = 0;
	while(1)
	{
		test = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		rl_on_new_line();
		//pause();
		buffer = readline("\033[1mminishell$> \033[m");
		 if (!buffer)
		 {
			 break;
		 }
		if (line_empty(buffer))
		{
			free(buffer);
			continue;
		}
		if (!ft_strcmp(buffer, "exit"))
		{
			free (buffer);
			return (write(2, "exit\n", 5), 0);
		}
		if (ft_strlen(buffer))
		{
			add_history (buffer);
			head = ft_lexer(buffer,envp);
			if(!ft_check(&head,buffer))
			{
				printf("minishell: syntax error\n");
				free(buffer);
				deleteList(&head);
				test = 1;
				continue ;
			}
			cmd = ft_parser(&head,buffer,g_env);
			// printf("the leng %d\n", cmd[0].num_cmds);
			open_files(cmd, cmd[0].num_cmds);
			execute_root(cmd, g_env);
		}
		// if(!test)
		// 	deleteList(&head);
		// free_all(cmd);
		// free(buffer);
	}
	return 0;
}