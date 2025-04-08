NAME = philo_bonus 
FILES = parsing_bonus.c task_bonus.c utils_bonus.c main_bonus.c fill_struct.c
FLAGES =  -Wall -Werror -Wextra #`-pthread -fsanitize=address
cc = cc 
OBJ = $(FILES:.c=.o)
RM = rm -rf
HEADER = philo_bonus/philo_bonus.h

%.o: %.c $(HEADER)
	$(cc) $(FLAGES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(cc) $(FLAGES) $(OBJ) -o $(NAME) -lpthread

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all