#include <ncurses.h>
#include <unistd.h> // For usleep
#include <stdlib.h>   // For srand and rand
#include <time.h>     // For time
#include "../include/game.h"

int display_menu() {
    int choice = 0;
    int input;

    while (1) {
        clear();
        mvprintw(5, 10, "Game Over!");
        mvprintw(7, 10, "1. Play Again");
        mvprintw(8, 10, "2. Exit");
        mvprintw(10, 10, "Use UP/DOWN arrow keys to select, ENTER to confirm.");
        mvchgat(7 + choice, 10, -1, A_REVERSE, 0, NULL); // Highlight choice
        refresh();

        input = getch();
        switch (input) {
            case KEY_UP: // Move up
                choice = (choice - 1 + 2) % 2;
                break;
            case KEY_DOWN: // Move down
                choice = (choice + 1) % 2;
                break;
            case '\n': // Enter key
                return choice;
        }
    }
}

void start_game() {
    int max_x, max_y;
    int menu_choice;

    do {

    // Initialize variables
    Snake snake;
    Food food;
    int ch;
    bool running = true;
    int score = 0;
    int current_delay = BASE_DELAY;

    // Initialize game window
    getmaxyx(stdscr, max_y, max_x);
    init_snake(&snake, max_x / 2, max_y / 2);

    // Generate the first food
    srand(time(NULL)); // Seed the random number generator once
    generate_food(&food, &snake, max_x, max_y);

    while (running) {
        // Non-blocking input
        timeout(0);
        ch = getch();

        // Change direction
        switch (ch) {
            case KEY_UP:
                if (snake.dy == 0) { snake.dx = 0; snake.dy = -1; current_delay = VERTICAL_DELAY; }
                break;
            case KEY_DOWN:
                if (snake.dy == 0) { snake.dx = 0; snake.dy = 1; current_delay = VERTICAL_DELAY; }
                break;
            case KEY_LEFT:
                if (snake.dx == 0) { snake.dx = -1; snake.dy = 0; current_delay = BASE_DELAY; }
                break;
            case KEY_RIGHT:
                if (snake.dx == 0) { snake.dx = 1; snake.dy = 0; current_delay = BASE_DELAY; }
                break;
            case 'q': // Quit the game
                running = false;
                break;
        }

        // Clear the screen
        clear();

        // Draw the borders
        for (int x = 0; x < max_x; x++) {
            mvaddch(0, x, '#');
            mvaddch(max_y - 1, x, '#');
        }
        for (int y = 0; y < max_y; y++) {
            mvaddch(y, 0, '#');
            mvaddch(y, max_x - 1, '#');
        }

        // Display the score
        mvprintw(0, 2, "Score: %d", score);

        // Draw the food
        mvprintw(food.y, food.x, "*");

        // Draw the snake
        for (int i = 0; i < snake.length; i++) {
            mvprintw(snake.segments[i].y, snake.segments[i].x, "O");
        }

        // Refresh the screen
        refresh();

        // Move the snake
        move_snake(&snake);

        // Check if the snake eats the food
        if (snake.segments[0].x == food.x && snake.segments[0].y == food.y) {
            grow_snake(&snake); // Grow the snake
            generate_food(&food, &snake, max_x, max_y); // Generate new food
            score++; // Increment score
        }

        // Adjust speed based on snake length
        if (snake.dx != 0) { // Horizontal movement
            current_delay = BASE_DELAY - (snake.length * 1000);
            if (current_delay < MIN_BASE_DELAY) {
                current_delay = MIN_BASE_DELAY;
            }
        } else if (snake.dy != 0) { // Vertical movement
            current_delay = VERTICAL_DELAY - (snake.length * 1000);
            if (current_delay < MIN_VERTICAL_DELAY) {
                current_delay = MIN_VERTICAL_DELAY;
            }
        }

        // Check collisions with borders
        if (snake.segments[0].x <= 0 || snake.segments[0].x >= max_x - 1 ||
            snake.segments[0].y <= 0 || snake.segments[0].y >= max_y - 1) {
            running = false; // End the game if the snake hits a border
        }

        // Check collisions with itself
        if (detect_self_collision(&snake)) {
            running = false; // End the game if the snake collides with itself
        }

        // Delay for smooth movement
        usleep(current_delay);
    }

    // Update best score if needed
    if (score > best_score) {
    best_score = score; // Update the best score
    }

    // End message
    clear();
    mvprintw(max_y / 2, (max_x / 2) - 5, "Game Over!");
    mvprintw((max_y / 2) + 1, (max_x / 2) - 9, "Score: %d", score);
    mvprintw((max_y / 2) + 2, (max_x / 2) - 9, "Best Score: %d", best_score); // Display best score
    mvprintw((max_y / 2) + 3, (max_x / 2) - 9, "Press any key to continue...");
    refresh();
    timeout(-1); // Wait indefinitely for a key press
    getch(); // Wait for user input

    // Display menu and handle choice
    menu_choice = display_menu();
    }
    while (menu_choice == 0); // Loop back if the player chooses "Play Again"
}