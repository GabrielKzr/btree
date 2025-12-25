CC = gcc

SRC_DIR = src
OBJ_DIR = bin
INC_DIR = inc

CFLAGS = -Wall -Wextra -I${INC_DIR} # -Werror -std=c11 -I$(INC_DIR) #-Wno-implicit-function-declaration

TARGET = main

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run:
	@./$(TARGET)