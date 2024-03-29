/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 01:42:29 by snouae            #+#    #+#             */
/*   Updated: 2022/07/06 21:02:06 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>

# define MAX_BUF 200
# define ERROR	-1
# define TRUE 1
# define FALSE 0

enum e_tokens
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

typedef struct s_data
{
	char	**g_env;
	int		st_err;
	int		g_status;
}	t_data;

t_data	g_data;

enum	e_fileType
{
	NONE,
	IN,
	OUT,
	HEREDOC,
	APPEND
};

typedef struct s_list
{
	int				len;
	int				type;
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_redirection
{
	char					*file;
	int						type;
	int						fd;
	int						status;
	int						st_herdoc;
	int						redirect_fd[2];
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char					**cmd;
	int						num_cmds;
	int						pipe[2];
	int						*prev;
	int						*next;
	int						is_builtin_in;
	int						exec;
	struct s_redirection	*redirect;
}		t_command;

void			ft_reset_io(int fd[]);
void			ft_save_io(int fd[]);
char			**copy_env(char **envp);
t_list			*ft_lexer(char *line);
t_list			*ft_add(char *line, int start, int end, int type);
int				search_token(char token);
int				ft_strlen(char *s);
int				ft_check(t_list **head);
t_command		*ft_parser(t_list **head);
char			**ft_split(char const *s, char c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup_n(char *src);
char			*ft_strjoin_n(char *s1, char *s2);
char			*expander(char *var, char **envp);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			serach_dollar(t_list **head, char **envp);
char			*fill_array(char *line, int start, int end);
int				search_token(char token);
void			open_files(t_command *cmd, int leng);
int				cherche_symbol(char c, char *str);
void			deletelist(t_list **head_ref);
void			free_all(t_command *cmd);
void			deleteredir(t_redirection **head_ref);
int				ft_heredoc(char *eof);
void			multi_heredoc_generator(t_command *data,
					int index, char *eof, int *pipe_heredoc);
void			redirect_handler_heredoc(t_command *data,
					int i, int *pipe_heredoc);
void			heredoc_core(char *line, char *eof,
					int pipe_heredoc[2]);
char			*check_dollar(int *j, char *str, char *new, char **env);
void			add_to_child(t_command *data, int i);
void			heredoc_core_2(char	*line, int pipe_heredoc[2]);
int				line_empty(char *str);
char			*ft_itoa(int nb);
void			ft_mark_redirect(char *line, int *i, int type, t_list **head);
void			add_qoute(int type, int test, int *i, char *line);
void			ft_mark_quote(char *line, int *i, int type, t_list **head);
void			ft_mark_dollar(char *line, int *i, int type, t_list **head);
void			ft_mark(char *line, int *i, int type, t_list **head);
char			*remove_single_quote(char *str);
char			*remove_double_quote(char *str, char **env);
char			*handl_herdoc(char *str);
char			*check(char *str, char **env, t_list **tmp, int *test);
t_redirection	*fill_riderect(char *str, t_list **tmp, char **env);
void			ft_lstadd_back1(t_redirection **lst, t_redirection *new);
void			ft_handler_dollar(t_list **tmp, char **env, char **join);
char			*check_dollar(int *j, char *str, char *new, char **env);
int				check_cases(t_list **current);
int				count_commads(t_list **head);
char			**copy_env(char **envp);
int				skip_redirect(char *str);
void			handler(int sig);
int				ft_check(t_list **head);
int				builtin_root(char **argv);
int				builtin_cd(int argc, char **argv);
int				builtin_echo(int argc __attribute((unused)), char **argv);
int				builtin_env(int argc __attribute((unused)),
					char **argv __attribute((unused)));
int				path_no_found(char **argv);
int				builtin_exit(int argc, char **argv);
void			builtin_exit_2(char **argv, int rtn_numeric);
int				exit_core(int argc, char **argv, int rtn_numeric);
int				atoi_sup(char *str, long *neg);
void			exported_vars_additional(char **dup_env);
void			check_numeric(char *arg, int *rtn_numeric);
bool			error_symbol(char *argv);
int				builtin_export(int argc, char **argv);
char			*skip_symbol(char *argv);
int				skip_redirect(char *str);
int				export_2(char **argv, char *new, int i);
void			exported_vars(void);
char			**sort_env(char **env);
bool			check_arg(char *argv);
char			*join_to_env(char	*env);
int				builtin_check(char *str);
int				builtin_pwd(int argc __attribute((unused)),
					char **argv __attribute((unused)));
int				builtin_unset(int argc __attribute((unused)), char **argv);
void			capital_handler(char *str);
int				env_init(char **env);
bool			check_var_is_char(char c);
char			*search_env(char *name);
char			*get_value(char *name);
bool			check_var_is_char(char c);
int				unset_the_var(char *name);
int				put_the_var(char *str);
int				set_the_env(char *name, char *value);
long long		ft_atoi_exit(const char *str, int i, int *status_error);
void			ft_command_not_found(char **paths, char *cmd);
int				open_file(t_redirection *redirect);
void			redirect_handler(t_command *data, int index);
void			redirect_in_handler(t_command *data, int i, int c, int n);
void			execute_root(t_command *data, char **envp);
int				execute_core(t_command *data, int i, char **envp);
int				open_dir_handler(t_command *data, int i);
void			execute_child(t_command *data, int i, char **envp);
int				exit_status(t_command *data, int i);
void			dup_io(t_command *data, int i);
void			status_generator(t_command *data, int i, int pid);
void			redirect_out_append(t_command *data, int i, int c, int n);
int				replace_str_env(char *old_str, char *new_str);
char			*get_path(char **envp, t_command *data, int index);
int				env_count(char **env);
int				add_to_env(char *str);
int				remove_from_env(char *str);
void			ft_free_env(void);
char			*ft_strchr_export(const char *s, int c);
bool			check_replace(char *old_str, char *new_str);
void			freememory(char **mem);
int				wordlen(char const *s, char c);
int				ft_wordcount(char const *s, char c);
int				ft_isalnum(int c);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(char *s1);
char			*ft_strjoin(char*s1, char *s2);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char			*ft_substr(char *s, unsigned int start, size_t len);
int				ft_error(char *shell_name, char *s1, char *message);
int				ft_error_malloc(char *shell_name, char *s1, char *message);
void			free_cmd(t_list **head, t_command *cmd, char *buffer);

#endif
