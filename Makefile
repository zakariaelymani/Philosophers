NAME = philo
FILES = mandatory/filler_and_init.c  mandatory/main.c mandatory/parsing.c mandatory/print_file.c \
mandatory/task.c mandatory/utils.c 
header =  mandatory/philo.h
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
	
