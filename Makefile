CC := gcc

INCLUDE_DIRS := $(shell find include -type d)
INCLUDE_TEST_DIRS := $(shell find tests/include -type d)
INCLUDE_DEPENDENCY_DIRS := $(shell find vendor -type d)

INCLUDES := $(addprefix -I,$(INCLUDE_DIRS)) $(addprefix -I,$(INCLUDE_DEPENDENCY_DIRS)) $(addprefix -I,$(INCLUDE_TEST_DIRS))

CFLAGS := -Wall -Wextra $(INCLUDES)
LDFLAGS := -lcurl

SRC_DIR := src
OBJ_DIR := build/obj
BIN_DIR := build/bin
DEP_DIR := vendor

SRC := $(filter-out $(SRC_DIR)/main.c, $(shell find $(SRC_DIR) -name '*.c'))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
MAIN_OBJ := $(OBJ_DIR)/main.o

OUT = $(BIN_DIR)/pine

TEST_DIR := tests
TEST_SRC := $(shell find $(TEST_DIR) -name '*.c')
TEST_OUT := $(BIN_DIR)/test_runner

DEP_SRC := $(filter-out $(DEP_DIR)/main.c $(DEP_DIR)/munit/example.c, $(shell find $(DEP_DIR) -name '*.c'))

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
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Pattern rule to build object files into build/obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

# Special rule for main.o
$(MAIN_OBJ): $(SRC_DIR)/main.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

# Test target
test: $(TEST_SRC) $(SRC) $(DEP_SRC)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TEST_OUT) $(TEST_SRC) $(SRC) $(DEP_SRC) $(LDFLAGS)
	./$(TEST_OUT)

# Clean up build artifacts
clean:
	rm -rf build/

.PHONY: all run test clean
