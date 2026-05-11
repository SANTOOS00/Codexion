NAME_PROGRAN = codexion
CC = cc

FLAGS = -pthread -g3 -fsanitize=thread

SRC = codexion.c \
	  init_or_clean_resource/init_simulation.c \
	  init_or_clean_resource/coders.c \
	  init_or_clean_resource/dongles.c \
	  init_or_clean_resource/free_2d_array.c\
	  init_or_clean_resource/init_or_destory_mutex_cond.c\
	  init_or_clean_resource/clean_resource.c\
      parse_args/parse_args.c \
	  threads_orchestrator.c\
	  monitor.c\
	  start_coders_in_simulation.c\
	  execute_coder_workflow.c\
	  return_dongles.c\
	  execute_coding_cycle.c\
	  pick_up_dongle.c\
	  init_or_clean_resource/queue_pro.c\
	  init_or_clean_resource/queue_fifo.c\
	  priority_queue.c\
	  time_utils.c

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
