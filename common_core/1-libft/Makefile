# =========================================================
# Compiler / Archiver
# =========================================================

CC      = gcc
AR      = ar
ARFLAGS = rcs

# =========================================================
# Project
# =========================================================

NAME = libft

# =========================================================
# Directories
# =========================================================

SRC_DIR      = src
TEST_SRC_DIR = tests
INC_DIR      = include
BUILD_DIR    = build

STATIC_DIR = $(BUILD_DIR)/static
SHARED_DIR = $(BUILD_DIR)/shared
OBJ_DIR    = $(BUILD_DIR)/obj
OBJ_STATIC = $(OBJ_DIR)/static
OBJ_SHARED = $(OBJ_DIR)/shared
TEST_DIR   = $(BUILD_DIR)/tests

# =========================================================
# Library output
# =========================================================

STATIC_LIB       = $(STATIC_DIR)/$(NAME).a

SHARED_MAJOR     = 1
SHARED_VERSION   = $(SHARED_MAJOR).0.1
SHARED_SONAME    = $(NAME).so.$(SHARED_MAJOR)
SHARED_LIB       = $(SHARED_DIR)/$(NAME).so.$(SHARED_VERSION)
SHARED_LIB_MAJOR = $(SHARED_DIR)/$(SHARED_SONAME)
SHARED_LINK      = $(SHARED_DIR)/$(NAME).so

# =========================================================
# Flags
# =========================================================

CFLAGS  = -Wall -Wextra -Werror -Wpedantic -std=c11 -O2
CFLAGS += -I$(INC_DIR) -MMD -MP

PIC_FLAGS = -fPIC

LDFLAGS = -L$(STATIC_DIR) -lft

SHARED_LDFLAGS = -shared -Wl,-soname,$(SHARED_SONAME)

# =========================================================
# Debug
# =========================================================

DEBUG_FLAGS = -g3 -DLIBFT_DEBUG -fsanitize=address,undefined

debug: CFLAGS  += $(DEBUG_FLAGS)
debug: LDFLAGS += -fsanitize=address,undefined
debug: all

# =========================================================
# Sources and objects
# =========================================================

SRC         = $(wildcard $(SRC_DIR)/*/*.c)
OBJ_STATICS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_STATIC)/%.o, $(SRC))
OBJ_SHAREDS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_SHARED)/%.o, $(SRC))
DEP_STATICS = $(OBJ_STATICS:.o=.d)
DEP_SHAREDS = $(OBJ_SHAREDS:.o=.d)

TESTS     = $(wildcard $(TEST_SRC_DIR)/*/*.c)
TEST_BINS = $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_DIR)/%, $(TESTS))

# =========================================================
# Main targets
# =========================================================

all: static tests

static: $(STATIC_LIB)

shared: $(SHARED_LIB)

tests: $(TEST_BINS)

# =========================================================
# Build rules
# =========================================================

$(OBJ_STATIC)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_SHARED)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PIC_FLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJ_STATICS)
	@mkdir -p $(STATIC_DIR)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Built static library: $@"

$(SHARED_LIB): $(OBJ_SHAREDS)
	@mkdir -p $(SHARED_DIR)
	$(CC) $(SHARED_LDFLAGS) -o $@ $^
	ln -sfn $(notdir $@) $(SHARED_LIB_MAJOR)
	ln -sfn $(notdir $(SHARED_LIB_MAJOR)) $(SHARED_LINK)
	@echo "Built shared library: $@"

$(TEST_DIR)/%: $(TEST_SRC_DIR)/%.c $(STATIC_LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

# =========================================================
# Run tests
# =========================================================

test: all
	@echo ""
	@echo "========================================"
	@echo " Running test suite"
	@echo "========================================"
	@PASS=0; FAIL=0; \
	for bin in $(TEST_BINS); do \
		if [ -f $$bin ]; then \
			echo ""; \
			echo "--- $$bin ---"; \
			$$bin; \
			if [ $$? -eq 0 ]; then \
				PASS=$$((PASS+1)); \
			else \
				FAIL=$$((FAIL+1)); \
			fi; \
		fi; \
	done; \
	echo ""; \
	echo "========================================"; \
	echo " Suites: $$PASS passed, $$FAIL failed"; \
	echo "========================================"; \
	[ $$FAIL -eq 0 ]

test_ds: all
	@for bin in $(TEST_DIR)/ds/*; do \
		if [ -f $$bin ]; then \
			echo "--- $$bin ---"; \
			$$bin; \
		fi; \
	done

# =========================================================
# Install / Uninstall
# =========================================================

PREFIX ?= /usr/local

install: static shared
	@mkdir -p $(PREFIX)/include $(PREFIX)/lib
	cp $(INC_DIR)/libft.h $(PREFIX)/include/
	cp $(STATIC_LIB) $(PREFIX)/lib/
	cp -a $(SHARED_DIR)/$(NAME).so* $(PREFIX)/lib/
	@echo "Installed libft to $(PREFIX)"

uninstall:
	rm -f $(PREFIX)/include/libft.h
	rm -f $(PREFIX)/lib/libft.a
	rm -f $(PREFIX)/lib/$(NAME).so
	rm -f $(PREFIX)/lib/$(NAME).so.$(SHARED_MAJOR)
	rm -f $(PREFIX)/lib/$(NAME).so.$(SHARED_VERSION)
	@echo "Removed libft from $(PREFIX)"

# =========================================================
# Cleanup
# =========================================================

clean:
	rm -rf $(BUILD_DIR)

fclean: clean

re: fclean all

# =========================================================
# Dependency files
# =========================================================

-include $(DEP_STATICS)
-include $(DEP_SHAREDS)

# =========================================================
# Phony
# =========================================================

.PHONY: all static shared tests test test_ds debug install uninstall clean fclean re
