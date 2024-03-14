NAME	=	minishell

CC	=	gcc

CFLAGS	=	-Wall -Werror -Wextra

SRC_PATH	=	srcs/

OBJ_PATH	=	objs/

SRC	=			main.c \

OBJ	=	$(SRC:.c=.o)

OBJS	=	$(addprefix $(OBJ_PATH), $(OBJ))

INCS	=	-I	./includes/

all:	$(OBJ_PATH) $(NAME)


$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
			mkdir $(OBJ_PATH)

$(NAME):	${OBJ_PATH} $(OBJS)
	@echo "\033[0;33m\nCOMPILING minishell...\n"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1;32m ./minishell created\n"

clean:
		rm -rf $(OBJ_PATH)

fclean:	clean
		rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re