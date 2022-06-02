/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:50:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/02 18:26:46 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int env_init(void)
{
    extern char **env;
    int count;
    int i;
    
    i = 0;
    count = 0;
    while (env && env[count])
        i++;
    if (i == 0)
        return (NULL);
    g_env = (char **)malloc((i + 1) * sizeof(char *));
    // if (!g_env)
    //     it should print an error message with a sytnax like bash does
    i = 0;
    while (env[i])
    {
        g_env[i] = ft_strdup(env[i]);
        if (!g_env[i])
        {
            // free the address of the g_env
            // return an error message with a systax like bash does
        i++;
    }
    g_env[i] = NULL;
    return (0);
}

char    *get_value(char *name)
{
    char    *env;
    env = search_env(name);
    if (env != 0)
        return (ft_strchr(env, '=') + 1); // HOME=/USER/AOUMAD (input) ==> /USER/AOUMAD (output)
    else
        return (NULL);
}
// khasni nchof blan dyal len_name likaduir operations dyal char pointer
char    *search_env(char *name)
{
    int len_name;
    int i;
    
    if (name == NULL || g_env == NULL)
        return (NULL);
    // if (ft_strchr(name, '=') != NULL)
    //     len_name = ft_strlen(ft_strchr(name, '=')) - ft_strlen(name);
    // else
    len_name = ft_strlen(name);
    i = 0;
    while (g_env[i])
    {
        if (!ft_strncmp(name, g_env[i], len_name) && 
            g_env[i][len_name] != NULL)
            return (g_env[i]);
        i++;
    }
    return (NULL);
}

bool    check_var_is_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}