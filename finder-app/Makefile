NAME=writer

CC=$(CROSS_COMPILE)gcc
FLAGS=-Wall -Werror -Wextra
DEBUG_FLAGS=-g -fsanitize=address
SRC=*.c
LIBS=
OBJ=
RM =rm -rf

# Build default target
all: $(NAME)

# Build writer target application
$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS)

# Clean object files
clean_obj:
	$(RM) $(OBJ)

# Clean binaries and object files
clean_bin: clean_obj
	$(RM) $(NAME)

# Clean all
clean: clean_obj clean_bin

# Remove binaries and rebuild
rebuild: clean_bin all

# Run re-builded target (for testing only)
run: rebuild
	./$(NAME) test_file test_string

# Remove binaries and re-build with debug
debug: clean_bin
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(SRC) -o $(NAME) $(LIBS)

# Run re-builded target for debug (for testing only)
run_debug: clean_bin debug
	./$(NAME) test_file test_string

# From:
# https://www.oreilly.com/library/view/managing-projects-with/0596006101/ch03.html

# Append like +=
# simple := $(simple) new stuff
# This is not allowed! (like in C/C++)
# recursive = $(recursive) new stuff

# Set if undefined with ?=
# OUTPUT_DIR ?= $(PROJECT_DIR)/out

