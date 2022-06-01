/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:41:31 by aoumad            #+#    #+#             */
/*   Updated: 2022/05/31 18:12:52 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef UTILS_H
# define UTILS_H

// ===== builtin_utils ==== //
int replace_str_env(char ***env, char *old_str, char *new_str);
int env_count(char **env);
int add_to_env(char ***env, char *str);
int remove_from_env(char ***env, char *str);

#endif