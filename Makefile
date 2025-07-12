CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
NAME = philo
SRCS = ./parse.c ./utils.c ./philo.c ./philo_routine.c ./ft_atol.c

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
