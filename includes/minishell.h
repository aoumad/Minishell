/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:24:52 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/17 04:12:58 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
#include <stdbool.h>
#include <stddef.h>

# define MAX_BUF 200
# define ERROR	-1
enum tokens
{
    pip = '|',
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
char	                **g_env;
// pid_t				g_pid;
// int					g_error;
int						g_status;
int                     g_exit_value;
// int					g_tester;
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
    char                    *file;
    int                     type;
    int	                    fd;
    struct s_redirection*   next;
} t_redirection;

typedef struct s_command
{
    char    **cmd;
    int     num_cmds; //cmd[0]
    int     pipe_fd[2];
    struct s_redirection *redirect;
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
int    builtin_root(char **argv);
int     builtin_cd(int argc, char **argv);
int     builtin_echo(int argc __attribute((unused)), char **argv);
int     builtin_env(int argc __attribute((unused)),
    char **argv __attribute((unused)));
int     builtin_exit(int argc, char **argv);
int     builtin_export(int argc, char **argv);
void    exported_vars(void);
int     builtin_check(char  *str);
int     builtin_pwd(int argc __attribute((unused)), 
    char **argv __attribute((unused)));
int     builtin_unset(int argc __attribute((unused)), char **argv);


//======================================
// ==== ENV ===== //
int     env_init(char **env);
bool    check_var_is_char(char c);
char    *search_env(char *name);
char    *get_value(char *name);
bool    check_var_is_char(char c);

// ==== ENV MODIFY ====//
int unset_the_var(char  *name);
int put_the_var(char *str);
int set_the_env(char *name, char *value);
#include <stdbool.h>

//=======================================
//======= Execute utils ===== //
char    *get_path(char **envp,  t_command *data);
void    ft_command_not_found(char **paths, char *cmd);
int open_file(t_redirection *redirect);

//====== execute function =====//
char    **ft_exec(t_command *data, char **envp, int index);
char    **execute_process_builtin(t_command *data, int index, char  **envp);
void    close_fd(t_command *data, int index, t_list *list);
char    **execute_root(t_command *data, char **envp);

//========================================
// ===== builtin_utils ==== //
int     replace_str_env(char ***env, char *old_str, char *new_str);
int     env_count(char **env);
int     add_to_env(char ***env, char *str);
int     remove_from_env(char ***env, char *str);
void	ft_free_env(char ***env);


//=========================================
// ======== libft ============ //
void	freememory(char **mem);
int	wordlen(char const *s, char c);
int	ft_wordcount(char const *s, char c);
char	**fill(char **split, char const *s, char c);
char	**ft_split(char const *s, char c);

int	    ft_isalnum(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//====== Error === //
int ft_error(char *shell_name, char *s1, char *message);

//======== main ======//
int     main(int argc, char **argv, char **envp);
char	**ft_copy_tab(char **envp);
void	ft_print_title(void);
char	*ft_readline_signal(char *line, t_command *data, int index);
void	ft_sigquit(int sig);
void	ft_sigint(int sig);

#endif