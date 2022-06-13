/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:30:42 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/13 10:33:04 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    
#include "../includes/minishell.h"

/*int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
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
}*/

void	ft_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit(int sig)
{
	(void)sig;
}

char	*ft_readline_signal(char *line, char **env, t_command *data, int index)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	line = readline("\033[1;35m~Minishell$\033[0m ");
	if (!line)
	{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(data[index].cmd[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_tabs(env);
			exit(2);
	}
	return (line);
}

void	ft_print_title(void)
{
	printf("\033[1;35m\
	 __  __ _       _     _          _ _ \n\
	|  \\/  (_)_ __ (_)___| |__   ___| | |\n\
	| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n\
	| |  | | | | | | \\__ \\ | | |  __/ | |\n\
	|_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\033[0m \
	\t\t\tby Diane & Balkis\n\n");
}

char	**ft_copy_tab(char **envp)
{
	int		i;
	int		size;
	char	**env;

	size = 0;
	i = -1;
	while (envp[++i])
		size++;
	env = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int main(int argc, char **argv, char **envp)
{

	char		*line;
	t_command	data;
	t_list		list;
	int index;
	
	index = 0;
	g_env = ft_copy_tab(envp);
	if (argc != 1)
		return (ft_putstr("Error: not argument accepted\n"), 1);
	ft_print_title();
	while (1)
	{
		line = ft_readline_signal(line, g_env, &data, index);
		if (line[0] != NULL)
		{
			g_env = execute_root(&data, g_env, &list, argv);
		}
		free(line);
	}
    return 0;
}