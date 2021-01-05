##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## make a file
##

SRC 	=	src/minishell.c						\
			src/my_putstr.c						\
			src/my_str_to_word_array.c 			\
			src/my_getenv.c 					\
			src/my_str_allocate_and_cat.c		\
			src/my_strcmp.c 					\
			src/my_strdup.c 					\
			src/linked_list.c 					\
			src/environment.c 					\
			src/my_strlen.c 					\
			src/my_strncmp.c 					\
			src/case_of_cd.c 					\
			src/my_strndup.c 					\

OBJ 	= 	$(SRC:.c=.o)

CC		=	gcc -g3

NAME	=	mysh

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		rm -rf $(OBJ)

test_run:
		gcc -o unit_test bonus/test_with_multiple_flags.c $(SRC) -lcriterion
		./unit_test

fclean:		clean
		rm -rf $(NAME)

re:		fclean all
