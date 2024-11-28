NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main_mandotiry.c \
	parsing/parsing.c \
	threads/threads.c threads/init_threads.c threads/routine.c \
	threads/eat_sleep_think.c threads/select_philo_forks.c \
	printing/printing.c \
	timer/timer.c  \
	frees_mlc_mtx/frees.c 

OBGS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	$(CC) $(OBGS) -o $(NAME) -lpthread

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBGS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 