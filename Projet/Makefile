CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = main
SRC = main.c analyseur_lexical.c
OBJ = $(SRC:.c=.o)

.PHONY: all run clean

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJ) $(NAME)
