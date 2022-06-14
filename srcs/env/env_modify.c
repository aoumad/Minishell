/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:01:28 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/14 18:12:30 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int unset_the_var(char  *name)
{
    char    *env_var;
        
    env_var = search_env(name);
    if (env_var == NULL)
        return (ERROR);
    remove_from_env(&g_env, env_var);
    return (0);
}

int put_the_var(char *str)
{
    // bach i7tli var there are two cases:
    // 1- the var already exists in env
    // so the solution is to replace it with the new one
    // 2- the var is new so we will append it
    //hence we gonna need to put two variables (old_var,new_var)
    // leeeeeeeees gooooo
    char    *new_var;
    char    *old_var;
    int     status;

    if (str == NULL || ft_strchr(str, '=') == NULL)
        return (ERROR);
    new_var = ft_strdup(str);
    if (new_var == NULL)
        return (ft_error("minishell", NULL, strerror(ENOMEM)));
    old_var = search_env(str);
    status = replace_str_env(&g_env, old_var, new_var);
    if (status == ERROR)
    {
        status = add_to_env(&g_env, new_var);
        if (status == ERROR)
            return (ft_error("minishell", NULL, strerror(ENOMEM)));
    }
    return (0);
}

int set_the_env(char *name, char *value)
{
    char    *var;
    int     status;
    
    if (name == NULL || value == NULL)
        return (ERROR);
    var = ft_strjoin(name, "=");
    if (var == NULL)
        return (ft_error("minishell", NULL, strerror(ENOMEM)));
    var = ft_strjoin(var, value);
    if (var == NULL)
        return (ft_error("minishell", NULL, strerror(ENOMEM)));
    status = put_the_var(var);
    free(var);
    return (status);
} 