NAME	=	minishell

CC	=	gcc

CFLAGS	= -Wall -Werror -Wextra -lreadline -g

SRC_PATH	=	srcs/
OBJ_PATH	=	objs/
LIBFT_PATH	=	./includes/libft/

LIBFT_FILE		=	libft.a

SRC	=	main.c \
\
		add_signal/add_signal.c \
\
		builtins/echo/echo.c \
		builtins/echo/quote.c \
		builtins/echo/double_quote.c \
		builtins/echo/simple_str.c \
		\
		builtins/pwd.c \
\
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
\
		get_pwd/get_pwd.c \
\
		prompt/get_prompt.c \
		prompt/gest_readline_recover.c \
\
		utiles/recover_word.c \
		utiles/utiles_for_echo.c \

OBJ	=	$(SRC:.c=.o)

OBJS	=	$(addprefix $(OBJ_PATH), $(OBJ))
LIBFT_LIB		=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

LIBFT_EX		=	$(LIBFT_LIB) $(CFLAGS)

INCS	=	-I	./includes/

all:	$(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
			mkdir $(OBJ_PATH)
			mkdir $(OBJ_PATH)/add_signal
			mkdir $(OBJ_PATH)/builtins
			mkdir $(OBJ_PATH)/builtins/echo
			mkdir $(OBJ_PATH)/get_pwd
			mkdir $(OBJ_PATH)/get_next_line
			mkdir $(OBJ_PATH)/prompt
			mkdir $(OBJ_PATH)/utiles

libft:
	@echo "\033[0;33m\nCOMPILING LIBFT $(LIBFT_PATH)\n"
	@make -sC $(LIBFT_PATH)
	@echo "\033[1;32mLIBFT created\n"

$(NAME):	libft ${OBJ_PATH} $(OBJS)
	@echo "\033[0;33m\nCOMPILING minishell...\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_EX) -o $(NAME)
	@echo "\033[1;32m ./minishell created\n"

clean:
		rm -rf $(OBJ_PATH)
		make -sC $(LIBFT_PATH) clean

fclean:	clean
		rm -rf $(NAME)
		rm -rf $(LIBFT_PATH)/libft.a

re:	fclean all

.PHONY:	all clean fclean re