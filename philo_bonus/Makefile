NAME	=	philo_bonus
HEAD	=	philo_bonus.h

SRC		=	main_bonus.c \
				src/initialisation_bonus.c \
				src/utils_bonus.c \
				src/daily_bonus.c \
				src/inspection_bonus.c
OBJ		=	$(SRC:%.c=%.o)
D_FIL	=	$(SRC:%.c=%.d)

FLAG	=	-g -Wall -Werror -Wextra

CC		=	gcc -O2 -MD
RM		=	rm -f

.PHONY		:	all clean fclean re bonus

all			:	$(NAME) Makefile

bonus		:	 all $(NAME_B) Makefile

$(NAME)		:	$(OBJ)
	$(CC) $(FLAG) $(OBJ) -o $(NAME)
	@echo "✅	Philosophers are ready to eat, think, sleep and die. Enjoy     ✅ "

libmake	:
	@make -C $(LIB_DIR)

%.o		:	%.c $(HEAD) $(HEAD_B)
	$(CC) $(FLAG) -c $< -o $@

include $(wildcard $(D_FIL))

clean		:
	$(RM) $(OBJ) $(D_FIL) $(OBJ_B) $(D_FIL_B)

fclean		:	clean
	$(RM) $(NAME) $(NAME_B)

re		:	fclean all