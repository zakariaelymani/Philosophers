NAME = philo
FILES = filler_and_init.c  main.c parsing.c print_file.c \
task.c utils.c 
header =  mandatory/philo.h
FLAGES = -Wall -Werror -Wextra -fsanitize=thread -pthread
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
	
