NAME	=	minishell

CC	=	gcc

CFLAGS	= -Wall -Werror -Wextra -lreadline

SRC_PATH	=	srcs/
OBJ_PATH	=	objs/
LIBFT_PATH	=	./includes/libft/

LIBFT_FILE		=	libft.a

SRC	=			main.c \

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