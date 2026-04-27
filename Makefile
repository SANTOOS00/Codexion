NAME_PROGRAN = codexion
CC = cc

FLAGS = -pthread -g3 -fsanitize=thread -std=c89

SRC = main.c\
      parse_args.c\
	  get_or_create_dongles.c\
      get_or_create_coders.c\
	  assign_dongles_to_coders.c\
	  run_coders_threads.c\
	  free_memory.c\
	  manger_monitor.c\
	  get_or_create_queue.c\
	  fifo.c\
	  edf.c

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
