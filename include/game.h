#ifndef GAME_H
#define GAME_H

#include "../include/game.h"
#include "../include/snake.h"
#include "../include/utils.h"

#define BASE_DELAY 150000      // Initial delay for horizontal movement
#define VERTICAL_DELAY 200000  // Initial delay for vertical movement
#define MIN_BASE_DELAY 50000   // Minimum delay for horizontal movement
#define MIN_VERTICAL_DELAY 70000 // Minimum delay for vertical movement

static int best_score = 0; // Stores the best score across sessions

// Function prototypes
void start_game();
void generate_food(Food *food, Snake *snake, int max_x, int max_y);

#endif