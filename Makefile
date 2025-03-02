NAME = philo
FILES = main.c
FLAGES = -Wall -Werror -Wextra -pthread
cc = cc
OBJ = $(FILES:.c=.o)
RM = rm -rf

%.o: %.c 
	$(cc) $(FLAGES) -c $< -o $@

all: $(NAME)


$(NAME): $(OBJ)
	$(cc) $(FLAGES) $(OBJ) -o $(NAME) -lpthread
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
	
