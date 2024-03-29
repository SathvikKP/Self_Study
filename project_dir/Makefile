# Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Isrc

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files
UTILS_SRC = $(wildcard $(SRC_DIR)/utils/*.c)
LINKEDLIST_SRC= $(wildcard $(SRC_DIR)/LinkedLists/*.c)
#TOPIC_B_SRC = $(wildcard $(SRC_DIR)/topicB/*.c)
MAIN_SRC = $(SRC_DIR)/main.c
ALL_SRC = $(UTILS_SRC) $(LINKEDLIST_SRC) $(MAIN_SRC)

# Object files
UTILS_OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(UTILS_SRC))
LINKEDLIST_OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(LINKEDLIST_SRC))
#TOPIC_B_OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(TOPIC_B_SRC))
MAIN_OBJ = $(BUILD_DIR)/main.o
ALL_OBJ = $(UTILS_OBJ) $(LINKEDLIST_OBJ) $(MAIN_OBJ)

# Target executable
TARGET = $(BIN_DIR)/runme

# Default target
all: $(TARGET)

# Linking object files to create the executable
$(TARGET): $(ALL_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compiling source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) output.txt

# Phony targets
.PHONY: all clean

# Additional targets for individual files
utils: $(UTILS_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/utils

LinkedLists: $(LINKEDLIST_OBJ) $(UTILS_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/LinkedLists

#topicB: $(TOPIC_B_OBJ) $(TOPIC_A_OBJ) $(HELPER_OBJ)
#	@mkdir -p $(BIN_DIR)
#	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/topicB