/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:24:52 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/10 11:08:22 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "env.h"
#include "utils.h"

# define MAX_BUF 200
# define ERROR	-1
enum tokens
{
    pipe = '|',
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

/*
my global variables
*/
extern char 			**g_env;
// pid_t					g_pid;
// int						g_error;
int						g_status;
// int						g_tester;
struct s_builtins
{
	char	*name;
	int		(*func)(int argc, char **argv);
};

typedef enum s_filetype
{
    NONE,
    IN,
    OUT,
    APPEND,
    HEREDOC,
}	t_filetype;
typedef struct s_list
{
    int len;
    int type;
    char *str;
    struct s_list* next;
} t_list;

typedef struct s_redirection
{
    char *file;
    int type;
    struct s_redirection* next;
} t_redirection;

typedef struct s_command
{
    char    **cmd;
    int     num_of_args;
    int     pipe_fd[2];
    int	    fd_stdout;
	int	    fd_stdin;
    struct s_redirection *redirect;
    char    *executable;
}        t_command;


// env variable list (using double struct)
/*typedef struct s_env_var {
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
*/


//====== lexer ======//
int     search_token(char token);
int     ft_leaxer(char *line);
void    ft_fill(char *line, int start, int end);

//====== main =======//
int main(int argc, char **argv, char **env);
int	ft_strcmp(char *s1, char *s2);


// ===== builtin functions ====== //
void    builtin_root(char **argv, t_cmd *cmd);
int builtin_cd(int argc, char **argv);
int builtin_echo(int argc __attribute((unused)), t_cmd *cmd);
int builtin_env(int argc __attribute((unused)),
    char **argv __attribute((unused)));
int builtin_exit(int argc, char **argv);
int builtin_export(int argc, char **argv);
int builtin_pwd(int argc __attribute((unused)), 
    char **argv __attribute((unused)));
int builtin_unset(int argc __attribute((unused)), char **argv);
#endif