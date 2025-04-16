# LIBRARIES
LIB_DIR=lib/libft
LIB_NAME=libft.a

# SOURCE FILES
FREE_SRC=$(wildcard src/free/*.c)
FREE_OBJ=$(FREE_SRC:.c=.o)

SHELL_SRC_FILES=$(wildcard src/shell/*.c)
SHELL_OBJ_FILES=$(SHELL_SRC_FILES:.c=.o)

ENVIRONMENT_SRC=$(wildcard src/environments/*.c)
ENVIRONMENT_OBJ=$(ENVIRONMENT_SRC:.c=.o)

BUILTINS_SRC=$(wildcard src/builtins/*.c)
BUILTINS_OBJ=$(BUILTINS_SRC:.c=.o)

TOKENIZER_SRC=$(wildcard src/tokenizer/*.c)
TOKENIZER_OBJ=$(TOKENIZER_SRC:.c=.o)

EXECUTION_SRC=$(wildcard src/execution/*.c)
EXECUTION_OBJ=$(EXECUTION_SRC:.c=.o)

OBJECT_FILES=$(FREE_OBJ) $(SHELL_OBJ_FILES) $(BUILTINS_OBJ) $(ENVIRONMENT_OBJ) $(TOKENIZER_OBJ) $(EXECUTION_OBJ)

# VARIABLES
COMPILER=cc
EXECUTABLE=minishell
COMPILER_FLAGS=-Wall -Werror -Wextra -Iincludes -g3 -fsanitize=address
LINKER_FLAGS=-lreadline -L$(LIB_DIR) -lft

# COLORS
GREEN=\033[0;32m
CYAN=\033[0;36m
YELLOW=\033[0;33m
RESET=\033[0m

.PHONY: all clean fclean re

%.o: %.c
	@echo "${CYAN}Compiling: $<${RESET}"
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

all: $(EXECUTABLE)

$(EXECUTABLE): $(LIB_NAME) $(OBJECT_FILES)
	@echo "${YELLOW}Linking object files to create $(EXECUTABLE)...${RESET}"
	$(COMPILER) $(COMPILER_FLAGS) $(OBJECT_FILES) -o $(EXECUTABLE) $(LINKER_FLAGS)
	@echo "${GREEN}Compilation successful! You can now run ./$(EXECUTABLE)${RESET}"

$(LIB_NAME):
	@echo "${CYAN}Building libft...${RESET}"
	make -C $(LIB_DIR)

clean:
	@echo "${YELLOW}Cleaning object files...${RESET}"
	make clean -C $(LIB_DIR)
	rm -f $(OBJECT_FILES)

fclean: clean
	@echo "${YELLOW}Removing executable and cleaning all files...${RESET}"
	make fclean -C $(LIB_DIR)
	rm -f $(EXECUTABLE)

re: fclean all
