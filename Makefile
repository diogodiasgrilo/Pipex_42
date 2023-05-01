NAME = pipex

LIBFT = libft.a

SRCS =	./srcs/pipex_main.c \
		./srcs/pipex_children.c \
		./srcs/pipex_errors.c \
		./srcs/pipex_args.c

BNS_SRCS = ./srcs/bonus/p_b_main.c \
			./srcs/bonus/p_b_args.c \
			./srcs/bonus/p_b_children.c \
			./srcs/bonus/p_b_errors.c		

OBJS :=$(SRCS:.c=.o)

BNS_OBJS :=$(BNS_SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
	@echo "$(GREEN)Bu-pau...pipex MADE!$(DEFAULT)"

$(NAME): $(OBJS)
	@echo "$(ORANGE)Compiling libraries...$(DEFAULT)"
	@make -C ./libft
	@mv ./libft/$(LIBFT) .
	@cc $(CFLAGS) $(OBJS) -L. $(LIBFT) -o $(NAME) -fsanitize=address

bonus: $(BNS_OBJS)
	@echo "$(ORANGE)Compiling libraries for bonus...$(DEFAULT)"
	@make -C ./libft
	@mv ./libft/$(LIBFT) .
	cc $(CFLAGS) -fsanitize=address $(LIBFT) $(BNS_OBJS) -o $(NAME)
	@echo "$(GREEN)Bonus compiled and completed!$(DEFAULT)"

tester: $(SRCS)
	make -C ft_printf
	mv ./libft/$(LIBFT) .
	cc $(CFLAGS) $(LIBFT) $(SRCS)
clean:
	@make clean -C ./libft
	@rm -f $(LIBFT)
	@rm -f $(BNS_OBJS)
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "$(ORANGE)Cleaning...yup, that's it!$(DEFAULT)"

re: fclean all

.PHONY: all tester clean bonus fclean re

#COLORS                                                                         
GREEN = \033[1;32m
RED = \033[1;31m
ORANGE = \033[38;5;208m
DEFAULT = \033[0m
YELLOW = \033[1;33m
