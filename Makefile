CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lncurses
SRC = src/main.c src/snake.c src/game.c src/utils.c
OBJ = $(SRC:.c=.o)
TARGET = snake
DEP = $(OBJ:.o=.d)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking $(TARGET)..."
	@$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

clean:
	@echo "Cleaning up..."
	@rm -f $(OBJ) $(DEP) $(TARGET)

run: $(TARGET)
	@./$(TARGET)