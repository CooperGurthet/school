// draws the map and entities

// #include "../include/rogue.h"
#include <rogue.h>

// TODO: draw border around the map
void drawMap(void)
{
    for (int y = 0; y < MAP_HEIGHT; y++) // iterate through first array
    {
        for (int x = 0; x < MAP_WIDTH; x++) // iterate through second array
        {
            if (map[y][x].visible) // checks if the tile is visible

            {
                mvaddch(y, x, map[y][x].ch | map[y][x].color); // draws the tile as visible
            }
            else if (map[y][x].seen) // check if the tile has been seen
            {
                mvaddch(y, x, map[y][x].ch | COLOR_PAIR(SEEN_COLOR)); // draws the tile as seen
            }
            else
            {
                mvaddch(y, x, ' '); // draws the tile as empty
            }
        }
    }
}

void drawEntity(Entity *entity)
{
    mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color); // draw given entity at its respective position and color
}

void drawInventory()
{
    /**
     * Draw the base inventory design
     *
     * For item in list of items in inventory
     * Draw name on new line
     *
     */
}

void drawEverything(void)
{
    clear();            // clears map
    drawMap();          // draws map
    drawEntity(player); // draws the player
}