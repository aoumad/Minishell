/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:32:21 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/12 16:22:46 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXEC_H
# define EXEC_H

//======= Execute utils ===== //
char    *get_path(char **envp,  t_command *data);
void    ft_command_not_found(char **paths, char *cmd, t_command *data);
int open_file(t_redirection *redirect, char **env);

//====== execute function =====//


#endif