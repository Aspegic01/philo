CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
NAME = philo
SRCS = $(shell ls ./*.c)

OFILES = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(FLAGS) $(OFILES) -o $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY:
