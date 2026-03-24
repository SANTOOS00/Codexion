# NAME_PROGEAM = 	codexion
# CC = cc
# FLAGS = -Wall -Wextra -Werror

# SRC_FILE = main.c parsion.c


# OBG = $(SRC_FILE:.c=.o)

# all : $(NAME_PROGEAM)

# $(NAME_PROGEAM): $(OBG)
#     $(CC) $(FLAGS) $(OBG) -o $(NAME_PROGEAM)


# %.o: %.c codexion.h
#     $(CC) $(FLAGS) -c $< -o $@

NAME_PROGRAM = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror

SRC_FILE = main.c parsion.c

OBJ = $(SRC_FILE:.c=.o)

all: $(NAME_PROGRAM)

$(NAME_PROGRAM): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME_PROGRAM)

%.o: %.c codexion.h
	$(CC) $(FLAGS) -c $< -o $@
# NAME_PROGRAM = codexion
# CC = gcc
# FLAGS = -Wall -Wextra -Werror
# SRC_FILE = main.c parsion.c

# OBJ = $(SRC_FILE:.c=.o)

# all: $(NAME_PROGRAM)

# $(NAME_PROGRAM): $(OBJ)
#     $(CC) $(FLAGS) $(OBJ) -o $(NAME_PROGRAM)

# %.o: %.c codexion.h
#     $(CC) $(FLAGS) -c $< -o $@

# clean:
#     rm -f $(OBJ) $(NAME_PROGRAM)