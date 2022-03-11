// Engine to handle all things related to the player

// #include "../include/rogue.h"
#include <rogue.h>

Entity *createPlayer(Position start_pos) // assigns the position and symbol for the player then creates it
{
    Entity *newPlayer = calloc(1, sizeof(Entity)); // creates a new entity called player

    newPlayer->pos.y = start_pos.y;               // sets the y position of the player to the value of the start position y
    newPlayer->pos.x = start_pos.x;               // sets the x position of the player to the value of the start position x
    newPlayer->ch = '@';                          // sets the symbol of the player
    newPlayer->color = COLOR_PAIR(VISIBLE_COLOR); // sets the color of the player

    return newPlayer;
}

void handleInput(int input) // engine to handleInputs
{
    Position newPos = {player->pos.y, player->pos.x}; // position of the player

    switch (input) // switch case since checking for the same value
    {
    // move up
    case 'w':
        newPos.y--;
        break;
    // move down
    case 's':
        newPos.y++;
        break;
    // move left
    case 'a':
        newPos.x--;
        break;
    // move right
    case 'd':
        newPos.x++;
        break;
    // open inventory
    case 'i':
        inventory();
        break;
    default:
        break;
    }
    movePlayer(newPos); // moves player
}

void movePlayer(Position newPos) // moves player
{
    if (map[newPos.y][newPos.x].walkable) // checks if the new tile player is on is walkable
    {
        // if it is moves the player
        clearFOV(player);         // clears the player's fov
        player->pos.y = newPos.y; // changes old y position to new y position
        player->pos.x = newPos.x; // changes old x position to new x position
        makeFOV(player);          // creates the player's fov
    }
    else
        ;
    // else don't move the player
}