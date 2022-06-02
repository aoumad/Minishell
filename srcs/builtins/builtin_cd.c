/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:25:11 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/02 19:04:57 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_cd(int argc, char **argv)
{
    char    *dir;

    dir = get_the_print_working_dir(argc, argv);
    if (dir == NULL)
        return (EXIT_FAILURE);
    if (chdir(dir) == -1)
        return (ERROR);
    // PRINT AN ERROR MESSAGE LIKE BASH DOES
    if (argv[1] && ft_strncmp(argv[1], "-", 2))
        ft_putendl_fd(dir, STDOUT_FILENO);
    if (update_pwd() == ERROR)
        return (EXIT_FAILURE);
}

char    *get_the_print_working_dir(int argc, char **argv)
{
    char    *dir;

    if (argc == 1)
    {
        dir = get_value("HOME");
        // if (dir == NULL)
        //     PRINT AN ERROR MESSAGE LIKE BASH DOES
    }
    else if (argv[1] && ft_strncmp(argv[1], "-", 2) == 0); // "cd -"
    {
        dir = get_value("OLDPWD");
        // if (dir == NULL)
        //     PRINT AN ERROR MESSAGE LIKE BASH DOES
    }
    else
        dir = get_value(argv[1]);
    return (dir);
}

int update_pwd()
{
    char    path[MAX_BUF];
    if (get_value("PWD")) // check if PWD exists for real in g_env ---- to handle weird cases
    { // like "cd dlfkdsf" so if yes then i need to compare between OLDPWD and PWD 
        // if nothing changed that means bli rah trat chi haja b7al dik command liwrit  
        if (set_the_env("OLDPWD", get_value("PWD")) == ERROR)
            return (ERROR);
    }
    else // if no then i need to remove OLDPWD content and replace it 
        unset_the_var("OLDPWD"); // with the previous one before using cd
    // if (getcwd(path, MAX_BUF) == ERROR)
    // {
    //     PRINT AN ERROR MESSAGE LIKE BASH DOES IN THIS CASE
    // }
    if (set_the_env("PWD", path) == ERROR)
        return (ERROR);
    return (0);
}

