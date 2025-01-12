#ifndef UTILS_H
#define UTILS_H

#include "snake.h"
#include <stdbool.h> // For bool type

typedef struct {
    int x, y; // Food position
} Food; // Food structure is defined here

// Function prototypes
void generate_food(Food *food, Snake *snake, int max_x, int max_y);

#endif