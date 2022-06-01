/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:47:53 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/01 11:29:11 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

extern char **g_env;

// ==== ENV ===== //
char    search_env(char *name);
char    *get_value(char *name);
char    search_env(char *name);
bool    check_var_on_env(char c);
#endif