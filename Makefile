NAME_PROGRAN = codexion

CC = cc

FLAGS = -pthread  -fsanitize=thread -g3
#-Wall -Wextra -Werror

SRC = src/init/queue.c\
	  src/init/queue_normal.c\
	  src/init/init_simulation.c \
	  src/init/coders.c \
	  src/init/dongles.c \
	  src/init/free_2d_array.c\
	  src/init/init_or_destory_mutex_cond.c\
	  src/cleanup/clean_resource.c\
      src/parse_args/parse_args.c \
      src/parse_args/validate_numeric_arguments.c \
      src/parse_args/string_to_int.c \
      src/parse_args/error_handler.c \
      src/parse_args/parser_time_val.c \
      src/parse_args/parse_compiles_required.c \
      src/parse_args/ft_atoi.c \
	  src/coder_main_loop.c\
	  src/coder_routine.c\
	  src/exit_threads.c\
	  src/heapify_up_or_down.c\
	  src/main.c\
	  src/manager_simulation.c\
	  src/monitor_edf_mode.c\
	  src/monitor_fifo_mode.c\
	  src/run_fifo_or_edf_mode.c\
	  src/monitor_routine.c\
	  src/perform_coding.c\
	  src/pick_up_dongle.c\
	  src/priority_queue.c\
	  src/queue_normal_manager.c\
	  src/return_dongles.c\
	  src/thread_joiner.c\
	  src/time_utils.c\
	  src/start_coders_and_watcher.c\
	  src/watcher_routine.c



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

re: fclean all
