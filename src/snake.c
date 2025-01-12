#include <stdbool.h>
#include "../include/snake.h"

void init_snake(Snake *snake, int start_x, int start_y) {
    snake->length = 1; // Initial snake length
    snake->segments[0].x = start_x;
    snake->segments[0].y = start_y;
    snake->dx = 1; // Start moving to the right
    snake->dy = 0;
}

void move_snake(Snake *snake) {
    // Move each segment to the position of the previous segment
    for (int i = snake->length - 1; i > 0; i--) {
        snake->segments[i] = snake->segments[i - 1];
    }

    // Update the head position
    snake->segments[0].x += snake->dx;
    snake->segments[0].y += snake->dy;
}

void grow_snake(Snake *snake) {
    if (snake->length < MAX_SNAKE_LENGTH) {
        snake->length++;
    }
}

bool detect_self_collision(Snake *snake) {
    for (int i = 1; i < snake->length; i++) {
        if (snake->segments[0].x == snake->segments[i].x &&
            snake->segments[0].y == snake->segments[i].y) {
            return true; // Collision detected
        }
    }
    return false; // No collision
}