// main file
/**
 * @file main.c
 * @author @author Pixelatedlily (33810489+Pixelatedlily@users.noreply.github.com)
 * @brief roguelike made in c to be ported to arduino
 * @version 0.1
 * @date 2022-01-04
 */

/**
 * Initial code from https://dev.to/ignaoya/the-c-roguelike-tutorial-part-0-the-map-2hg
 * commented by me and additional code written by me
 */

// #include "../include/rogue.h"
#include <rogue.h>

// sets the size of the in game map
const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entity *player; // creates new entity called player
Tile **map;     // creates map array of tiles
                /*
                 * pointer to pointer
                 * first pointer points to array of arrays
                 * each pointer points to an array of tiles within big array of arrays
                 */

int main(void)
{
    Position start_pos;      // creates start position from tuple
    bool compatibleTerminal; // bool to check terminal compatibility

    compatibleTerminal = cursesSetup(); // check compatibility

    if (compatibleTerminal) // runs game if compatible
    {

        cursesSetup();     // initialize the terminal
        srand(time(NULL)); // creates seed for the map given the computer clock

        map = createMapTiles(); // creates the map
        start_pos = setupMap(); // makes the start position center of map
        // might change to random room
        player = createPlayer(start_pos); // creates player at start position

        gameLoop(); // starts game

        closeGame(); // ends game
    }
    else
    {
        endwin(); // ends game
    }

    return 0;
}