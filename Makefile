CC := gcc
INCLUDES := -Iinclude -Ivendor/minunit
CFLAGS := -Wall -Wextra $(INCLUDES)

SRC_DIR := src
OBJ_DIR := build/obj
BIN_DIR := build/bin

SRC := $(filter-out $(SRC_DIR)/main.c, $(shell find $(SRC_DIR) -name '*.c'))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
MAIN_OBJ := $(OBJ_DIR)/main.o

OUT = $(BIN_DIR)/pine

TEST_DIR := tests
TEST_SRC := $(shell find $(TEST_DIR) -name '*.c')
TEST_OUT := $(BIN_DIR)/test_runner

# Default target
all: $(OUT)

# Start the server
start:
	docker compose build
	docker compose watch

# Stop the server
stop:
	docker compose down

# Run the main executable
run: $(OUT)
	./$(OUT)

update-dependencies:
	git submodule update --init --recursive

# Link the object files + main.o into the executable
$(OUT): $(OBJ) $(MAIN_OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule to build object files into build/obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for main.o
$(MAIN_OBJ): $(SRC_DIR)/main.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Test target
test: $(TEST_SRC) $(SRC)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TEST_OUT) $(TEST_SRC)
	./$(TEST_OUT)

# Clean up build artifacts
clean:
	rm -rf build/

.PHONY: all run test clean
