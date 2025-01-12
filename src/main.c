#include <ncurses.h>
#include "../include/game.h"

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Welcome message
    printw("Welcome to Snake! Press any key to start...");
    refresh();
    getch(); // Wait for user input

    // Start the game
    start_game();

    // End ncurses
    endwin();
    return 0;
}