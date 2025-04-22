CC = gcc
INCLUDES = -Iinclude -Ivendor/minunit
CFLAGS = -Wall -Wextra $(INCLUDES)

SRC = src/main.c
OBJ = build/obj/main.o
OUT = build/bin/pine

TEST_SRC = tests/test_runner.c
TEST_OUT = build/bin/test_runner

# Default target
all: $(OUT)

# Run the main executable
run: $(OUT)
	./$(OUT)

# Build final executable from object file
$(OUT): $(OBJ)
	git submodule update --init --recursive
	mkdir -p build/bin
	$(CC) $(CFLAGS) -o $@ $^

# Compile source file into object file
$(OBJ): $(SRC)
	mkdir -p build/obj
	$(CC) $(CFLAGS) -c $< -o $@

# Test target
test: $(SRC) $(TEST_SRC)
	mkdir -p build/bin
	$(CC) $(CFLAGS) -o $(TEST_OUT) $(SRC) $(TEST_SRC)
	./$(TEST_OUT)

# Clean up build artifacts
clean:
	rm -rf build/

.PHONY: all run test clean
