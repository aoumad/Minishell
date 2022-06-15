NAME	= minishell

SRCS	=	srcs/builtins/builtin_cd.c srcs/builtins/builtin_echo.c srcs/builtins/builtin_env.c srcs/builtins/builtin_exit.c \
			srcs/builtins/builtin_export.c srcs/builtins/builtin_pwd.c srcs/builtins/builtin_root.c srcs/builtins/builtin_unset.c \
			srcs/env/env_modify.c srcs/env/env.c srcs/exec/exec_utils.c srcs/exec/exec.c \
			srcs/utils/builtin_utils.c srcs/utils/error.c srcs/libft/ft_isalnum.c srcs/libft/ft_memcpy.c srcs/libft/ft_putchar_fd.c \
			srcs/libft/ft_putendl_fd.c srcs/libft/ft_putstr_fd.c  srcs/libft/ft_split.c srcs/libft/ft_strchr.c  srcs/libft/ft_substr.c\
			srcs/libft/ft_strjoin.c srcs/libft/ft_strlen.c srcs/libft/ft_strncmp.c srcs/libft/ft_strnstr.c srcs/main.c
OBJS	= $(SRCS:.c=.o)
MAIN	= srcs/main.c

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

%.o : 		%.c
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

${NAME}:	${OBJS} includes/minishell.h
				@${CC} ${OBJS} -o ${NAME}
clean:
				@rm -f ${OBJS}
				
fclean:		clean
				@rm -f ${NAME}
				
re:			fclean all
