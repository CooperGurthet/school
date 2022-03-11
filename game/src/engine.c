// main engine to handle events in game

// #include "../include/rogue.h"
#include <rogue.h>

bool cursesSetup(void) // setsup the terminal for cutses
{
    initscr();        // initialize the terminal
    noecho();         // turns off echo
    curs_set(0);      // sets the cursor to the top left corner
    if (has_colors()) // checks if colors are enabled
    {
        start_color(); // curses color function

        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK); // creates pair of black background and white foreground with name visible_Color
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);     // creates pair of black background and blue foreground with name seen_Color
        return true;
    }
    else
    {
        mvprintw(20, 50, "Your system doesn't support color. Can't start game!");
        getch();
        return false;
    }
}

void gameLoop(void) // runs the game
{
    int ch; // ch will equal key presses

    makeFOV(player);  // sets the fov around the player
    drawEverything(); // draws the map and entities

    while (ch = getch()) // waits for user to press key
    {
        if (ch == 'q') // if exit key is pressed then stop loop
        {
            closeGame();
            break;
        }
        handleInput(ch);  // handles key presses
        drawEverything(); // draws the map and entities
    }
}

void closeGame(void) // ends game
{
    endwin();     // terminates ncurses
    free(player); // frees the memory allocated for player
}