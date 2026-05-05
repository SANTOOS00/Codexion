NAME_PROGRAN = codexion
CC = cc

FLAGS = -pthread -g3

#-g3 -fsanitize=thread

SRC = codexion.c \
      parse_args.c \
	  init_simulation.c \
	  coders.c \
	  dongles.c \
	  free_2d_array.c\
	  clean_resource.c\
	  init_or_destory_mutex_cond.c
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
