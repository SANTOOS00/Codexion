NAME_PROGRAN = codexion
CC = cc

FLAGS = -pthread 
# -g3 -fsanitize=thread
SRC = main.c\
      parse_args.c\
	  get_or_create_dongles.c\
      get_or_create_coders.c\
	  assign_dongles_to_coders.c\
	  push_stack.c\
	  run_coders_threads.c\
	  free_memory.c\
	  manger_monitor.c

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
