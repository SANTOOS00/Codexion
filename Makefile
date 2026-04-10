


NAME_PROGRAN = codexion

CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = main.c parse_args.c create_in_threads.c  join_in_threads.c

OBG = $(SRC:.c=.o)

all: $(NAME_PROGRAN)

$(NAME_PROGRAN): $(OBG)
	$(CC) $(FLAGS) $(OBG) -o $(NAME_PROGRAN)

%.o: %.c codexion.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBG)

fclean: clean
	rm -f $(NAME_PROGRAN)
