


NAME_PROGRAN = codexion

CC = cc

FLAGS =  -pthread -fsanitize=thread -g3

SRC = main.c parse_args.c manger_threads.c coders_registry.c

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
