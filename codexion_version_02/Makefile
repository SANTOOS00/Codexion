NAME_PROGRAN = codexion
CC = cc

FLAGS = -pthread -g3 -fsanitize=thread

SRC = codexion.c \
      parse_args.c \
	  init_simulation.c \
	  coders.c \
	  dongles.c \
	  free_2d_array.c\
	  init_or_destory_mutex_cond.c\
	  clean_resource.c\
	  threads_orchestrator.c\
	  monitor.c\
	  start_coders_in_simulation.c\
	  fifo_or_edf.c\
	  queue.c

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
