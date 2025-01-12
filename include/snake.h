#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define MAX_SNAKE_LENGTH 100

typedef struct {
    int x, y; // Position of the snake segment
} SnakeSegment;

typedef struct {
    SnakeSegment segments[MAX_SNAKE_LENGTH]; // Array of snake segments
    int length; // Current length of the snake
    int dx, dy; // Current direction of movement
} Snake;

// Function prototypes
void init_snake(Snake *snake, int start_x, int start_y);
void move_snake(Snake *snake);
void grow_snake(Snake *snake);
bool detect_self_collision(Snake *snake);

#endif