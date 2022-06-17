/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:30:42 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/17 04:45:59 by aoumad           ###   ########.fr       */
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

/*void	ft_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit(int sig)
{
	(void)sig;
}

char	*ft_readline_signal(char *line, t_command *data, int index)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	line = readline("\033[1;35m~Minishell$\033[0m ");
	if (!line)
	{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(data[index].cmd[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
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
}*/

int main(int argc, char **argv, char **envp)
{

	t_command	*data;
	int i;

	(void)argv;
	i = 0;
	//data = NULL;
	//data[0].cmd = NULL;
	//data[0].cmd[0] = NULL;
	g_env = NULL;
	(void)argc;
	/*if (argc == 1)
	{
		ft_putstr_fd("Error: not argument accepted\n", 1);
		return (1);
	}*/
    i = 0;
    while (envp[i])
    {
        i++;
    }
    if (i == 0)
        return (1);
    g_env = (char **)malloc((i + 1) * sizeof(char *));
    if (!g_env)
            printf("g_env is empty");
    i = 0;
    while (envp[i])
    {
        g_env[i] = ft_strdup(envp[i]);
        if (!g_env[i])
        {
            ft_free_env(&g_env);
            return (ft_error("minishell", NULL, strerror(ENOMEM)));
        }
        i++;
    }
    g_env[i] = NULL;
	//env_init(envp);
	// i = 0;
	// while (argv[i])
	// 	i++;
	
	// while (argv[i])
	// {
	// 	data[i].cmd[0] = argv[i + 1];
	// 	data->num_cmd++;
	// 	i++;
	// } 
	data = malloc(sizeof(t_command) * 2);
	/*data[0].cmd = malloc(sizeof(char) * 4);
	data[0].cmd[0] = "echo";
	data[0].cmd[1] = "-n";
	data[0].cmd[2] = "chwads";
	data[0].cmd[3] = NULL;*/
	data[0].cmd = malloc(sizeof(char) * 2);
	data[0].cmd[0] = "env";
	data[0].cmd[1] = NULL;
	data[0].num_cmds = 1;
	/*data[1].cmd = malloc(sizeof(char) * 2);
	data[1].cmd[0] = "cat";
	data[1].cmd[1] = 0;*/
	g_env = execute_root(data, envp);
	i = 0;
	// while (g_env[i])
	// {
	// 	printf("%s\n", g_env[i]);
	// 	i++;
	// }
    return 0;
}