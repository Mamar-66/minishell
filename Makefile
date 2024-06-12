NAME	=	minishell

CC	=	cc

CFLAGS	= -Wall -Werror -Wextra -g
LDFLAGS = -lreadline

SRC_PATH	=	srcs/
OBJ_PATH	=	objs/
LIBFT_PATH	=	./includes/libft/

LIBFT_FILE		=	libft.a

SRC	=	main.c \
		main_suite.c \
\
		ft_ex/ft_ex.c \
\
		add_signal/add_signal.c \
\
		builtins/echo/echo.c \
		builtins/echo/quote.c \
		builtins/echo/double_quote.c \
		builtins/echo/simple_str.c \
		builtins/export/export.c \
		builtins/export/export2.c \
		builtins/export/export3.c \
		builtins/export/export4.c \
		builtins/export/export5.c \
		builtins/export/export6.c \
		builtins/export/export7.c \
		builtins/export/export8.c \
		builtins/export/export9.c \
		builtins/export/export10.c \
		builtins/export/export11.c \
		builtins/export/export12.c \
		builtins/export/export13.c \
		builtins/export/export14.c \
		builtins/export/export15.c \
		builtins/export/export16.c \
		builtins/export/export17.c \
		builtins/export/export18.c \
		builtins/cd/cd.c \
		builtins/cd/cd2.c \
		builtins/cd/cd3.c \
		builtins/unset.c \
		builtins/exit.c \
		\
		builtins/pwd.c \
		builtins/env.c \
\
		get_pwd/get_pwd.c \
\
		parsing/parsing.c \
		parsing/redirect/redirect.c \
		parsing/redirect/redirect_suite.c \
		parsing/redirect/redirect_right.c \
		parsing/redirect/redirect_left.c \
		parsing/redirect/double_redirect_left.c \
		parsing/redirect/double_redirect_left_suite.c \
		parsing/redirect/verif_name_file.c \
		parsing/redirect/ft_redirect_for_father.c \
\
		pipex/ft_pipex.c \
		pipex/suite_pipex.c \
\
		prompt/get_prompt.c \
		prompt/gest_readline_recover.c \
\
		utiles/recover_word.c \
		utiles/utiles_for_echo.c \
		utiles/my_fonction_free/free_tab.c \
		utiles/initialisenv.c \
		utiles/my_ft_getenv.c \
		utiles/exit_bis.c \
		utiles/split_for_ex/split_for_ex.c \
\
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

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
			mkdir $(OBJ_PATH)/builtins/export
			mkdir $(OBJ_PATH)/builtins/cd
			mkdir $(OBJ_PATH)/get_pwd
			mkdir $(OBJ_PATH)/pipex
			mkdir $(OBJ_PATH)/parsing
			mkdir $(OBJ_PATH)/parsing/redirect
			mkdir $(OBJ_PATH)/prompt
			mkdir $(OBJ_PATH)/utiles
			mkdir $(OBJ_PATH)/utiles/my_fonction_free
			mkdir $(OBJ_PATH)/utiles/split_for_ex
			mkdir $(OBJ_PATH)/ft_ex
			mkdir $(OBJ_PATH)/get_next_line

libft:
	@echo "\033[0;33m\nCOMPILING LIBFT $(LIBFT_PATH)\n"
	@make -sC $(LIBFT_PATH)
	@echo "\033[1;32mLIBFT created\n"

$(NAME):	libft ${OBJ_PATH} $(OBJS)
	@echo "\033[0;33m\nCOMPILING minishell...\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_EX) $(LDFLAGS) -o $(NAME)
	@echo "\033[1;32m ./minishell created\n"

clean:
		rm -rf $(OBJ_PATH)
		make -sC $(LIBFT_PATH) clean

fclean:	clean
		rm -rf $(NAME)
		rm -rf $(LIBFT_PATH)/libft.a

re:	fclean all

.PHONY:	all clean fclean re