#include "../include/utils.h"
#include <stdbool.h>
#include <stdlib.h>

void generate_food(Food *food, Snake *snake, int max_x, int max_y) {
    bool valid_position;

    do {
        valid_position = true;

        // Generate random coordinates for food
        food->x = rand() % (max_x - 2) + 1; // Avoid borders
        food->y = rand() % (max_y - 2) + 1;

        // Check if food is generated on the snake
        for (int i = 0; i < snake->length; i++) {
            if (snake->segments[i].x == food->x && snake->segments[i].y == food->y) {
                valid_position = false;
                break;
            }
        }
    } while (!valid_position);
}