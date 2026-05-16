NAME_PROGRAN = codexion
CC = cc

FLAGS = -pthread #-g3 -fsanitize=thread
#valgrind --leak-check=full --track-origins=yes --verbose --num-callers=20
	#valgrind --tool=helgrind --verbose --num-callers=20 ./codexion
SRC = init_or_clean_resource/queue.c\
	  init_or_clean_resource/queue_normal.c\
	  init_or_clean_resource/init_simulation.c \
	  init_or_clean_resource/coders.c \
	  init_or_clean_resource/dongles.c \
	  init_or_clean_resource/free_2d_array.c\
	  init_or_clean_resource/init_or_destory_mutex_cond.c\
	  init_or_clean_resource/clean_resource.c\
      parse_args/parse_args.c \
	  coder_main_loop.c\
	  coder_routine.c\
	  exit_threads.c\
	  heapify_up_or_down.c\
	  main.c\
	  manager_simulation.c\
	  monitor_edf_mode.c\
	  monitor_fifo_mode.c\
	  monitor_routine.c\
	  perform_coding.c\
	  pick_up_dongle.c\
	  priority_queue.c\
	  queue_normal_manager.c\
	  return_dongles.c\
	  thread_joiner.c\
	  time_utils.c\
	  watcher_routine.c



# 	  controller.c\
# 	  execute_coder_workflow.c\
# 	  execute_coding_cycle.c\
# 	  monitor.c\
# 	  start_coders_in_simulation.c\
# 	  threads_orchestrator.c\
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
