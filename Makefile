# **************************************************************************** #
#                                  CONFIG                                      #
# **************************************************************************** #

# =========================================================
# Compiler
# =========================================================
CC              = cc

# =========================================================
# Directories
# =========================================================
SRC_DIR         = src
OBJ_DIR         = build/obj
BIN_DIR         = build/bin
INC_DIR         = include

# =========================================================
# Flags
# =========================================================
CFLAGS          = -Wall -Wextra -Werror
DEBUG_FLAGS     = -g3 -std=c11 -O2
SAN_FLAGS       = -fsanitize=address,undefined

INCLUDES        = -I$(INC_DIR)

# **************************************************************************** #
#                              SOURCES / OBJECTS                               #
# **************************************************************************** #

# Todos os arquivos .c dentro de src/**
#SRC              := $(wildcard $(SRC_DIR)/*/*.c)

SRC := $(shell find $(SRC_DIR) -type f -name "*.c")

# Objetos espelhando a estrutura
OBJS             := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nome dos binários
BINS             := $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #

GREEN            = \033[0;32m
RED              = \033[0;31m
BLUE             = \033[0;34m
YELLOW           = \033[1;33m
RESET            = \033[0m

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(BINS)

# =========================================================
# Build dos objetos
# =========================================================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(BLUE)Compiling object: $<$(RESET)"

# =========================================================
# Build dos binários individuais
# =========================================================
$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $< -o $@
	@echo "$(GREEN)Binary created: $@$(RESET)"

# **************************************************************************** #
#                                  CLEAN                                       #
# **************************************************************************** #

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(RESET)"

fclean: clean
	@rm -rf $(BIN_DIR)
	@echo "$(RED)Binaries removed$(RESET)"

re: fclean all

# **************************************************************************** #
#                                  DEBUG                                       #
# **************************************************************************** #

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re
	@echo "$(YELLOW)Debug build complete$(RESET)"

sanitize: CFLAGS += $(DEBUG_FLAGS) $(SAN_FLAGS)
sanitize: re
	@echo "$(YELLOW)Sanitizer build complete$(RESET)"

# **************************************************************************** #
#                                 EXECUTION                                    #
# **************************************************************************** #

run: all
	@for bin in $(BINS); do \
		echo "$(GREEN)Running $$bin$(RESET)"; \
		./$$bin; \
	done

valgrind: debug
	@for bin in $(BINS); do \
		echo "$(YELLOW)Valgrind $$bin$(RESET)"; \
		valgrind \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--track-fds=yes \
			./$$bin; \
	done

# **************************************************************************** #

.PHONY: all clean fclean re debug sanitize run valgrind
