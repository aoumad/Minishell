/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:30:42 by aoumad            #+#    #+#             */
/*   Updated: 2022/05/23 11:01:22 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    
#include "../includes/minishell.h"

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

int main(int argc, char **argv, char **env)
{
	while(1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		char *buffer = readline("Minishell> ");
		if (!buffer)
			return (write(2, "exit\n", 5), 1);
		if (!ft_strcmp(buffer, "exit"))
		{
			free (buffer);
			printf ("exit");
				exit(1) ;
		}
		if (ft_strlen(buffer))
			add_history (buffer);
		free(buffer);
    }
    return 0;
}