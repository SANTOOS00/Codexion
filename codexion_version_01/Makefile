NAME_PROGRAN = codexion
CC = gcc

FLAGS = -pthread 
#-g3 -fsanitize=thread

SRC = codexion.c\
      parse_args.c\
	  free.c\
	  initialize_coders.c\
	  initialize_dongles.c\
	  initialize_queue.c\
	  assign_dongles_to_coders.c\
	  push_queue.c\
	  is_queue_full.c

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
