NAME_PROGRAN = codexion

CC = cc

FLAGS = -pthread -Wall -Wextra -Werror

SRC = src/main.c\
	  src/cleanup/clean_resource.c\
	  src/cleanup/free_double_array.c\
	  src/coders/coders.c \
	  src/coders/init_coders.c \
	  src/coders/perform_coding.c \
	  src/coders/utils.c\
	  src/dongles/init_dongles.c\
	  src/dongles/pick_up_dongle.c\
	  src/dongles/return_dongles.c\
	  src/monitor/monitor_routine.c\
	  src/monitor/utils.c\
      src/parse_args/parse_args.c\
      src/parse_args/validate_numeric_arguments.c\
      src/parse_args/string_to_int.c\
      src/parse_args/error_handler.c\
      src/parse_args/parser_time_val.c\
      src/parse_args/ft_atoi.c\
	  src/queue/heapify_up_or_down.c\
	  src/queue/init_queue.c\
	  src/queue/priority_queue_utils.c\
	  src/queue/queue.c\
	  src/queue/utils.c\
	  src/simulation/init_simulation.c\
	  src/simulation/init_mutex_cond.c\
	  src/simulation/manager_simulation.c\
	  src/utils/exit_threads.c\
	  src/utils/print_action.c\
	  src/utils/thread_joiner.c\
	  src/utils/time.c\
	  src/watcher/run_scheduler.c\
	  src/watcher/watcher_routine.c\
	  src/watcher/utils.c


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
