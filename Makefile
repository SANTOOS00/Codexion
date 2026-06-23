NAME_PROGRAN = codexion

CC = cc

FLAGS =  -g3 -fsanitize=thread #-pthread -Wall -Wextra -Werror

SRC = src/init/queue.c\
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
	  src/monitor_routine.c\
	  src/get_status.c\
	  src/pick_up_dongle.c\
	  src/perform_coding.c\
	  src/queue_manager.c\
	  src/queue_pop_edf.c\
	  src/queue_pop_fifo.c\
	  src/priority_queue_utils.c\
	  src/check_coder_burnout.c\
	  src/return_dongles.c\
	  src/thread_joiner.c\
	  src/try_take_dongle.c\
	  src/time_utils.c\
	  src/watcher_routine.c



OBG = $(SRC:.c=.o)

all: $(NAME_PROGRAN)

$(NAME_PROGRAN): $(OBG)
	$(CC) $(FLAGS) $(OBG) -o $(NAME_PROGRAN)

%.o: %.c src/include/codexion.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBG)

fclean: clean
	rm -f $(NAME_PROGRAN)

re: fclean all
