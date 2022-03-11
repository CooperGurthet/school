// header allows functions to be run through separate files

// guards to stop compiler from generating this header file multiple times
#ifndef ROGUE_H
#define ROGUE_H

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2

// structs are similar to classes in object oriented languages
typedef struct // turns two ints into a position
{
    int y;
    int x;
} Position;

typedef struct // tile class for wall floor etc
{
    char ch;
    int color;
    bool transparent;
    bool visible;  // boolean to check if the tiles is currently visible
    bool seen;     // boolean to check if the tile has ever been seen
    bool walkable; // boolean to check if entities can walk on it
} Tile;

typedef struct // room class to easily create rooms
{
    int height;
    int width;
    Position pos;
    Position center;
} Room;

typedef struct // item class
{
    char ch;
    char name;
} Item;

// TODO: add fighting elements
typedef struct // gets position from entity
{
    Position pos;
    int color;
    char ch;
} Entity;

// draw.c functions
void drawMap(void);
void drawEntity(Entity *entity);
void drawInventory();
void drawEverything(void);

// engine.c functions
bool cursesSetup(void);
void gameLoop(void);
void closeGame(void);

// map.c functions
Tile **createMapTiles(void);
Position setupMap(void);
void freeMap(void);

// room.c functions
Room createRoom(int y, int x, int height, int width);
void addRoomToMap(Room room);
void connectRoomCenters(Position centerOne, Position centerTwo);

// fov.c functions
void makeFOV(Entity *player);
void clearFOV(Entity *player);
int getDistance(Position origin, Position target);
bool isInMap(int y, int x);
bool lineOfSight(Position origin, Position target);
int getSign(int a);

// inventory.c functions
void inventory();

// player.c functions
Entity *createPlayer(Position start_pos);
void handleInput(int input);
void movePlayer(Position newPos);

// externs
// stops c++ compiler from fucking this
// allows the transfer of variables between files
extern const int MAP_HEIGHT; // height of the map
extern const int MAP_WIDTH;  // width of the map
extern Entity *player;       // player variable
extern Tile **map;           // array of tiles that creates map
#endif