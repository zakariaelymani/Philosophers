NAME = philo_bonus 
FILES = parsing_bonus.c task_bonus.c utils_bonus.c main_bonus.c fill_struct_bonus.c
FLAGES =  -Wall -Werror -Wextra
cc = cc
OBJ = $(FILES:.c=.o)
RM = rm -rf
HEADER = philo_bonus.h

%.o: %.c $(HEADER)
	$(cc) $(FLAGES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(cc) $(FLAGES) $(OBJ) -o $(NAME) 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all