NAME_PROGRAN = codexion
CC = cc

FLAGS = -pthread -g3# -o2 -fsanitize=thread
#valgrind --leak-check=full --track-origins=yes --verbose --num-callers=20
	#valgrind --tool=helgrind --verbose --num-callers=20 ./codexion
SRC = init_or_clean_resource/queue.c\
	  init_or_clean_resource/coder_crossing.c\
	  init_or_clean_resource/init_simulation.c \
	  init_or_clean_resource/coders.c \
	  init_or_clean_resource/dongles.c \
	  init_or_clean_resource/free_2d_array.c\
	  init_or_clean_resource/init_or_destory_mutex_cond.c\
	  init_or_clean_resource/clean_resource.c\
      parse_args/parse_args.c \
	  coder_routine.c\
	  main.c \
	  manager_simulation.c\
	  exit_threads.c\
	  thread_joiner.c\
	  watcher_routine.c\
	  monitor_routine.c


# 	  controller.c\
# 	  crossing_manager.c\
# 	  execute_coder_workflow.c\
# 	  execute_coding_cycle.c\
# 	  monitor_edf_mode.c\
# 	  monitor_fifo_mode.c\
# 	  monitor.c\
# 	  pick_up_dongle.c\
# 	  priority_queue.c\
# 	  return_dongles.c\
# 	  start_coders_in_simulation.c\
# 	  threads_orchestrator.c\
# 	  time_utils.c\
# 	  watcher_tid.c


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
