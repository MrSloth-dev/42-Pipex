################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = pipex
CC = clang
CFLAGS = -Wall -Wextra -Werror -Iincludes -g

CLR_RMV = \033[0m
RED	    = \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
CYAN	= \033[1;36m
RM	    = rm -rf

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

vpath %.h includes
vpath %.c src
HEADER = pipex.h

PRINTF_DIR = ./includes/ft_printf/
PRINTF = ./includes/ft_printf/libftprintf.a

SRCS = main.c \
	   free.c \
	   utils.c \

OBJS = $(addprefix src/, $(SRCS:.c=.o))

################################################################################
#                                  Makefile  objs                              #
################################################################################

all : $(NAME) $(HEADER)

$(NAME) : $(OBJS) $(PRINTF)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(FLAGS) $(OBJS) $(PRINTF) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)ft_printf$(CLR_RMV)..."
	@echo "$(GREEN)ft_printf created[0m ✅"

$(PRINTF) : $(PRINTF_DIR)
	@make -C $(PRINTF_DIR) -s

clean :
	@ $(RM) *.o */*.o */*/*.o
	@ make clean -C $(PRINTF_DIR) -s
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✅"

fclean : clean
	@ $(RM) $(NAME) $(NAME_BONUS)
	@ make fclean -C $(PRINTF_DIR) -s
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✅"

re : fclean all

.PHONY : all clean fclean re
