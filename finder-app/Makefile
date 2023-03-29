NAME=writer

CC=gcc
FLAGS=-Wall -Werror -Wextra
DEBUG_FLAGS=-g -fsanitize=address
SRC=*.c
LIBS=
OBJ=
RM =rm -rf

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(LIBS) $(SRC) -o $(NAME)

clean_obj:
	$(RM) $(OBJ)

clean_bin: clean_obj
	$(RM) $(NAME)

clean: clean_obj clean_bin

rebuild: clean_bin all

run: rebuild
	./$(NAME) test_file test_string

debug: clean_bin
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(LIBS) $(SRC) -o $(NAME)

run_debug: clean_bin debug
	./$(NAME) test_file test_string
