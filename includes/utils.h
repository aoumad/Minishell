/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:41:31 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/05 18:40:15 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef UTILS_H
# define UTILS_H

// ===== builtin_utils ==== //
int replace_str_env(char ***env, char *old_str, char *new_str);
int env_count(char **env);
int add_to_env(char ***env, char *str);
int remove_from_env(char ***env, char *str);

//====== Error === //
int ft_error(char *shell_name, char *s1, char *message);

#endif