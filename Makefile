CC=gcc
FLAGS= -g
FILES= srcs/parsing/main.c srcs/parsing/tools.c srcs/parsing/ft_lexer.c \
		srcs/parsing/check_syntax.c srcs/parsing/parser.c srcs/parsing/ft_split.c \
		srcs/parsing/expander.c srcs/parsing/ft_riderct.c \
		srcs/builtins/builtin_cd.c srcs/builtins/builtin_echo.c srcs/builtins/builtin_env.c srcs/builtins/builtin_exit.c \
		srcs/builtins/builtin_export.c srcs/builtins/builtin_pwd.c srcs/builtins/builtin_root.c srcs/builtins/builtin_unset.c \
		srcs/env/env_modify.c srcs/env/env.c srcs/exec/exec_utils.c srcs/exec/exec.c \
		srcs/utils/builtin_utils.c srcs/utils/error.c srcs/libft/ft_isalnum.c srcs/libft/ft_memcpy.c srcs/libft/ft_putchar_fd.c \
		srcs/libft/ft_putendl_fd.c srcs/libft/ft_putstr_fd.c  srcs/libft/ft_split.c srcs/libft/ft_strchr.c  srcs/libft/ft_substr.c\
		srcs/libft/ft_strjoin.c srcs/libft/ft_strncmp.c srcs/libft/ft_strnstr.c srcs/libft/ft_strdup.c srcs/exec/save_io.c \
		srcs/exec/ft_heredoc.c srcs/exec/ft_redirect.c srcs/builtins/export_additional.c
OBJS= $(FILES:.c=.o)
NAME= minishell
INCLUDES=-I includes/minishell.h -I/Users/aoumad/.brew/opt/readline/include
READLINE=-lreadline -L/Users/aoumad/.brew/opt/readline/lib
RM= rm -rf
all: $(NAME) 

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $^ $(READLINE)  -o $(NAME)

%.o: %.c includes/minishell.h
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
