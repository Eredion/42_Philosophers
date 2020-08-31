NAME = a.out

SRCS = main.c utils.c init.c input.c

OBJS = $(SRCS:.c=.o)

GCC = gcc -pthread

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS)
	$(GCC) $(FLAGS) $(SRCS) -c
	$(GCC) $(OBJS) -o $(NAME)
	@echo Done!

clean:
	@echo Cleaning objects
	@rm -f $(OBJS)

fclean: clean
	@echo Cleaning $(NAME)
	@rm -f $(NAME) a.out

re: fclean all

test:	$(NAME)
	@echo Compiling and testing $(NAME)...
	@echo
	@./$(NAME)

.PHONY: all clean fclean re test
