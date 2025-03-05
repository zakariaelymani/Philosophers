NAME = philo
FILES = main.c  utils.c filler_and_init.c garbagecollecter.c parsing.c print_file.c task.c
header =  philo.h 
FLAGES = -Wall -Werror -Wextra -pthread -fsanitize=address
cc = cc
OBJ = $(FILES:.c=.o)
RM = rm -rf

%.o: %.c $(header)
	$(cc) $(FLAGES) -c $< -o $@

all: $(NAME)


$(NAME): $(OBJ)
	$(cc) $(FLAGES) $(OBJ) -o $(NAME) -lpthread
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
	
