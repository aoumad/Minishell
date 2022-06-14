/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:54:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/14 16:06:43 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void exported_vars(void);
static void sort_env(char **env);
static bool check_arg(char *argv);

int builtin_export(int argc, char **argv)
{
    int status;
    int  i;

    status = EXIT_SUCCESS;
    if (argc == 1)
        exported_vars();
    if (argc > 1)
    {
        i = 1;
        while (argv[i])
        {
            if (check_arg(argv[i]) == false)
            {
                ft_error("minishell", argv[i], "not a valid identifier");
                status = EXIT_FAILURE;
            }
            else if (ft_strchr(argv[i], '='))
                put_the_var(argv[i]);
            i++;
        }
    }
    return (status);
}

static void exported_vars(void)
{
    char    **dup_env;
    int     i;
    
    dup_env = (char **)malloc((env_count(g_env) + 1) * sizeof(char *)); // +1 for NULL
    if (dup_env == NULL)
    {
        ft_error("minishell", NULL, strerror(ENOMEM)); // "Cannot allocate memory" message
        return ;
    }   
    ft_memcpy(dup_env, g_env, (env_count(g_env) + 1) * sizeof(char *));
    sort_env(dup_env);
    i = 0;
    while (dup_env[i])
    {
        
    }
    free(dup_env);
}

static void sort_env(char **env)
{
    int     i;
    int     j;
    char    *tmp;
    int     count;
    
    count = env_count(env);
    i = 0;
    while(i < count - 1)
    {
        j = 0;
        while (j < (count - 1))
        {
            if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j]) + 1) > 0)
            {
                tmp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

static bool check_arg(char *argv)
{
    int i;

    i = 0;
    if (argv[0] == '\0' || argv[0] == '=')
        return (false);
    while (argv[i] != '\0'  && argv[i] != '=' &&    (argv[i]))
        i++;
    if (argv[i] == '=' || argv[i] == '\0')
        return (true);
    else
        return (false);
    
}