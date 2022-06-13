/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:12:36 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/13 11:59:50 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *ft_remove_quote(t_cmd *cmd);

int builtin_echo(int argc __attribute((unused)), t_command *cmd)
{
    int i;
    int num_words;
    int n_flag;

    i = 0;
    n_flag = 0;
    num_words = ft_lstsize(cmd);
    while (cmd->args[i])
    {
        if (!ft_strcmp((char *)cmd->args[i], "-n"))
            n_flag = 1;
        i++;
    }
    /*while (num_words)
    {
            ft_remove_quote(cmd);
        num_words--;
    }*/
    while (cmd->args[i])
    {
        ft_putstr_fd(cmd->args[i], 1);
        if (cmd->args[i + 1])
            ft_putstr_fd(' ', 1);
        i++;
    }
    if (n_flag == 0)
        ft_putchar_fd('\n', 1);
    return (0);
}

/*static int	ft_isin(const char *s, char *c)
{
    int i;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (NOT_FOUND);
}

static int	get_last_index(char const *s1, char const *set)
{
	int	len;

	len = ft_strlen(s1);
	while (--len >= 0)
		if (ft_isin(set, s1[len]) == NOT_FOUND)
			break ;
	return (len);
}*/

/*static char **ft_remove_quotes(t_cmd *cmd)
{
    int i;
    int j;
    char *str_to_trim;
    char *str;

    i = 0;
    j = 0;
    while (cmd->args[i])
    {
        while (ft_isin(cmd->args[i], "\"") != NOT_FOUND || ft_isin(cmd->args[i], "\"") != NOT_FOUND)
        {
            if (ft_isin(cmd->args[i], "\"") == NOT_FOUND)
                str = "\'";
            else if (ft_isin(cmd->args[i], "\"") == NOT_FOUND)
                str = "\'";
            str_to_trim = ft_substr(cmd->args[i], ft_isin(cmd->args[i], str),
                get_last_index(cmd->args[i], str));
            ft_strtrim(str_to_trim, str);
        }
    }
}*/