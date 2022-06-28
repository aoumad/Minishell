# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>

# define MAX_BUF 200
# define ERROR	-1
# define true 1
# define false 0
enum tokens
{
	pipe_token = '|',
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

/*
my global variables
*/
char	                **g_env;
int                     st_err;
// pid_t				g_pid;
// int					g_error;
int						g_status;
//int                     g_st;
int                     g_exit_value;
enum s_fileType
{
	NONE,
	IN,
	OUT,
	HEREDOC,
	APPEND
}   t_filetype;

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
    int fd;
    int status;
    int redirect_fd[2];
    struct s_redirection* next;
} t_redirection;
typedef struct s_command
{
	char	**cmd;
	int     num_cmds;
	int     pipe[2];
	int     *prev;
	int     *next;
	int     is_builtin_in;
	struct s_redirection *redirect;
}		t_command;

//======= oussama save io ======== yarbi tkhdm//
void    ft_reset_io(int fd[]);
void    ft_save_io(int fd[]);
char    **copy_env(char **envp);

t_list *ft_lexer(char *line , char **env);
t_list	*ft_add(char *line, int start, int end, int type);
int search_token(char token);
int	ft_strlen(char *s);
int ft_check(t_list** head, char *line);
t_command *ft_parser(t_list** head, char *line , char **env);
char	**ft_split(char const *s, char c);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup_n(char *src);
//char    *find_commande(char *cmd, char **envp);
char	*ft_strjoin_n(char *s1, char *s2);
char *expander(char *var, char **envp);
void    ft_lstadd_back(t_list **lst, t_list *new);
void serach_dollar(t_list** head, char **envp);
char *fill_array(char *line, int start, int end);
int search_token(char token);
void open_files(t_command *cmd, int leng);
int cherche_symbol(char c, char *str);
void deleteList(t_list** head_ref);
void free_all(t_command *cmd);
int    ft_heredoc(t_command *data, int index, char *eof);
void	heredoc_core(char *line, char *eof, int pipe_heredoc[2], int rtn_value);
void    multi_heredoc_generator(t_command *data, int index, char *eof, int *pipe_heredoc);
void    redirect_handler_heredoc(t_command *data, int i, int *pipe_heredoc);
char	*check_dollar(int *j, char *str, char *new, char **env);
int line_empty(char *str);
/////////////////
// ===== builtin functions ====== //
int    builtin_root(char **argv);
int     builtin_cd(int argc, char **argv);
int     builtin_echo(int argc __attribute((unused)), char **argv);
int     builtin_env(int argc __attribute((unused)),
	char **argv __attribute((unused)));
int     builtin_exit(int argc, char **argv);
void	builtin_exit_2(char **argv, int rtn_numeric);

//===== export ==========//
bool	error_symbol(char *argv);
int     builtin_export(int argc, char **argv);
char	*skip_symbol(char *argv);
int		export_2(char **argv, char *new, int test, int i);
void    exported_vars(void);
char	**sort_env(char **env);
bool	check_arg(char *argv);

int     builtin_check(char  *str);
int     builtin_pwd(int argc __attribute((unused)), 
	char **argv __attribute((unused)));
int     builtin_unset(int argc __attribute((unused)), char **argv);
void	capital_handler(char *str);


//======================================
// ==== ENV ===== //
int     env_init(char **env);
bool    check_var_is_char(char c);
char    *search_env(char *name);
char    *get_value(char *name);
bool    check_var_is_char(char c);

// ==== ENV MODIFY ====//
int 		unset_the_var(char  *name);
int 		put_the_var(char *str, int test);
int 		set_the_env(char *name, char *value);
long long	ft_atoi_exit(const char *str, int i, int *status_error);

//=======================================
//======= Execute utils ===== //
char    *get_path(char **envp,  t_command *data, int index);
void    ft_command_not_found(char **paths, char *cmd);
int     open_file(t_redirection *redirect);
void    redirect_handler(t_command *data, int index);

//====== execute function =====//
void execute_root(t_command *data, char **envp);
// int     execute_command(t_command *data, char **envp, int index, int pid);
// int    exec_1(t_command *data, int index, char **envp, int pid);
// int     ft_pipe_built(t_command *data, int pid, int index);

//========================================
// ===== builtin_utils ==== //
int     replace_str_env(char ***env, char *old_str, char *new_str, int test);
int     env_count(char **env);
int     add_to_env(char ***env, char *str);
int     remove_from_env(char *str);
void	ft_free_env(char ***env);


//=========================================
// ======== libft ============ //
void	freememory(char **mem);
int	wordlen(char const *s, char c);
int	ft_wordcount(char const *s, char c);

int	    ft_isalnum(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char*s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char *s, unsigned int start, size_t len);

//====== Error === //
int ft_error(char *shell_name, char *s1, char *message);

#endif