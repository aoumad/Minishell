/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:24:52 by aoumad            #+#    #+#             */
/*   Updated: 2022/05/25 15:47:28 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "../libft/libft.h"

# define ERROR	-1
enum tokens
{
    pipe = '|',
    token_and  = '&',
    redirect_out = '>',
    redirect_in = '<',
    dollar = '$',
    tab = '\t',
    single_quo = '\'',
    double_quo = '\"',
    white_space = ' ',
    char_null = 0,
    new_lin = '\n'
};
struct s_builtins
{
	char	*name;
	int		(*func)(int argc, char **argv);
};
typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*file;
	int				fd;
	int				token;
	char			*eof;
	unsigned int	num_of_args;
	struct s_token  *next;
}   t_cmd;

// env variable list (using double struct)
typedef struct s_env_var {
	unsigned int		sort_index;
	unsigned int		index;
	char				*name;
	char				*value;
	char				**both;
	struct s_env_var	*next;
}	t_env_var;

// env variable list 
typedef struct s_state {
	t_env_var	*path;
	t_env_var	*home;
	t_env_var	*env;
	t_cmd		*cmd;
	int			io[2];
	int			**fds;
	int			*pids;
	int			pipes;
	char		**env_tab;
	char		*line;
	char		*pwd;
	char		*old_pwd;
	int			man_err;
	int			status;
	int			sig;
	int			pid;
}	t_state;


typedef struct node
{
    t_cmd data;
    struct node* next;
} *t_node;

//====== lexer ======//
int     search_token(char token);
int     ft_leaxer(char *line);
void    ft_fill(char *line, int start, int end);

//====== main =======//
int main(int argc, char **argv, char **env);
int	ft_strcmp(char *s1, char *s2);

#endif