NAME_PROGRAN = codexion
CC = cc

FLAGS = -pthread 

#-g3 -fsanitize=thread

SRC = codexion.c \
      parse_args.c \
	  init_simulation.c \
	  utils.c \
	  coders.c \
	  dongles.c \
	  ft_free_resource.c

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
