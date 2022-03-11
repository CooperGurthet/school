// creates a map from arrays of tiles

/**
 * algorithm: http://roguebasin.com/?title=Dungeon-Building_Algorithm
 * 1 Fill the whole map with solid earth
 * 2 Dig out a single room in the centre of the map //british person wrote this article
 * 3 Pick a wall of any room
 * 4 Decide upon a new feature to build
 * 5 See if there is room to add the new feature through the chosen wall
 * 6 If yes, continue. If no, go back to step 3
 * 7 Add the feature through the chosen wall
 * 8 Go back to step 3, until the dungeon is complete
 * 9 Add the up and down staircases at random points in map
 * 10 Finally, sprinkle some monsters and items liberally over dungeon
 */

// #include "../include/rogue.h"
#include <rogue.h>

Tile **createMapTiles(void) // fills map with walls
{
    Tile **tiles = calloc(MAP_HEIGHT, sizeof(Tile *)); // allocates memory for the initial array

    for (int y = 0; y < MAP_HEIGHT; y++) // iterates through each array in the map
    {
        tiles[y] = calloc(MAP_WIDTH, sizeof(Tile)); // allocates memory for the map in each array
        for (int x = 0; x < MAP_WIDTH; x++)         // iterates through each inner array
        {
            tiles[y][x].ch = '#';                          // sets the symbol for each tile to #
            tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR); // sets the color of the tile
            tiles[y][x].walkable = false;                  // sets the boolean walkable to false to stop movement
            tiles[y][x].transparent = false;               // set boolean transparent to false so entities cant see through the tile
            tiles[y][x].visible = false;                   // set boolean visible to false so entities cant see it until they visit it
            tiles[y][x].seen = false;                      // set boolean seen to false so entities cant see it until they have visited it
        }
    }

    return tiles;
}
Position setupMap(void) // creates rooms and hallways
{
    int y, x, height, width, n_rooms;
    n_rooms = (rand() % 11) + 5;                 // the number of rooms to be created
    Room *rooms = calloc(n_rooms, sizeof(Room)); // allocate memory for the number of rooms
    Position start_pos;                          // center of room

    for (int i = 0; i < n_rooms; i++) // creates rooms until it reaches the randomly selected number of rooms
    {
        y = (rand() % (MAP_HEIGHT - 10)) + 1;       // randomly choose center y position
        x = (rand() % (MAP_WIDTH - 20)) + 1;        // randomly choose center x position
        height = (rand() % 7) + 3;                  // randomly choose height
        width = (rand() % 15) + 5;                  // randomly choose width
        rooms[i] = createRoom(y, x, height, width); // creates room array given its coordinates and size
        addRoomToMap(rooms[i]);                     // adds the room to the map array
        if (i > 0)
        {
            connectRoomCenters(rooms[i - 1].center, rooms[i].center);
        }
    }

    start_pos.y = rooms[0].center.y; // sets the characters y start position to the center of the 1st room
    start_pos.x = rooms[0].center.x; // sets the characters x start position to the center of the 1st room
    // could change to randomly created room not sure if it would be better

    free(rooms);

    return start_pos;
}

/**
 * @brief stops room overlap
Position setupMap(void)
{
  int y, x, height, width, n_rooms;
  n_rooms =  (rand() % 11) + 5;
  Room* rooms = calloc(n_rooms, sizeof(Room));
  Position start_pos;

  int rooms_counter = 0;

  for (int i = 0; i < n_rooms; i++)
  {
    y = (rand() % (MAP_HEIGHT - 10)) + 1;
    x = (rand() % (MAP_WIDTH - 20)) + 1;
    height = (rand() % 7) + 3;
    width = (rand() % 15) + 5;

    if (!roomOverlaps(rooms, rooms_counter, y, x, height, width))
    {
      rooms[rooms_counter] = createRoom(y, x, height, width);
      addRoomToMap(rooms[rooms_counter]);
      rooms_counter++;
    }
  }

  start_pos.y = rooms[0].center.y;
  start_pos.x = rooms[0].center.x;

  free(rooms);

  return start_pos;
}

bool roomOverlaps(Room* rooms, int rooms_counter, int y, int x, int height, int width)
{
  for (int i = 0; i < rooms_counter; i++)
  {
    if (x >= rooms[i].pos.x + rooms[i].width || rooms[i].pos.x >= x + width)
    {
      continue;
    }
    if (y + height <= rooms[i].pos.y || rooms[i].pos.y + rooms[i].height <= y)
    {
      continue;
    }

    return true;
  }

  return false;
}
 *
 */

void freeMap(void) // frees the memory allocated for the map function
{
    for (int y = 0; y < MAP_HEIGHT; y++) // iterates through each array in the map
    {
        free(map[y]); // frees the memory allocated for the map in each array
    }
    free(map); // frees the rest of the memory allocated for the map
}