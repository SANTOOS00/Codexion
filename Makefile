
NAME_PROGRAM = codexion
CC = cc
# FLAGS = -Wall -Wextra -Werror

SRC_FILE = main.c parsion.c

OBJ = $(SRC_FILE:.c=.o)

all: $(NAME_PROGRAM)

$(NAME_PROGRAM): $(OBJ)
	$(CC) $(OBJ) -o $(NAME_PROGRAM)

%.o: %.c codexion.h
	$(CC)  -c $< -o $@

fclean:
	rm -f $(OBJ)
