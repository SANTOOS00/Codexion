NAME_PROGEAM = 	codexion
CC = CC
FLAGS = -Wall -Wextra -Werror

SRC_FILE = main.c parsion.c


OBG = $(SRC_FILE:.c=.o)

all : $(NAME_PROGEAM)


$(NAME_PROGEAM) : $(OBG)
    $(CC) $(FLAGS) $(OBG) -o $(NAME_PROGEAM)

%.o:%.c codexion.h
    $(CC) $(FLAGS) -c $< -o $@


