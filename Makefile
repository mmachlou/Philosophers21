NAME = philo

GCC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread

SRC = src/initalize_philo.c \
	  src/initalize_table.c \
	  src/routin.c \
	  src/meals_simulation.c \
	  src/philosophers.c \
	  src/utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean flcean re