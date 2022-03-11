// creates rooms and hallways

#include <rogue.h>

Room createRoom(int y, int x, int height, int width) // creates room given x,y and height,width
{
    Room newRoom; // creates new room struct

    newRoom.pos.y = y;                        // sets new room y to given y
    newRoom.pos.x = x;                        // sets new room x to given x
    newRoom.height = height;                  // sets new room height to given height
    newRoom.width = width;                    // sets new room width to given width
    newRoom.center.y = y + (int)(height / 2); // sets new room center to the center of the room on the y
    newRoom.center.x = x + (int)(width / 2);  // sets new room center to the center of the room on the x

    return newRoom;
}

void addRoomToMap(Room room) // adds room to map array
{
    for (int y = room.pos.y; y < room.pos.y + room.height; y++) // iterates through the initial array
    {
        for (int x = room.pos.x; x < room.pos.x + room.width; x++) // iterates through the second array
        {
            map[y][x].ch = '.';           // sets the symbol for each new tile to .
            map[y][x].walkable = true;    // sets the boolean walkable to true to allow player to walk
            map[y][x].transparent = true; // sets the boolean transparent to true to allow player to see through the tile
        }
    }
}

void connectRoomCenters(Position centerOne, Position centerTwo) // connects rooms with hallways
{
    Position temp;        // temporary position use to carve out hallwa
    temp.x = centerOne.x; // sets the temp position x to the center of first room x
    temp.y = centerOne.y; // sets the temp positio ny to the center of first room y

    while (true) // loop until the temp position is equal to that of the second rooms center
    {
        if (abs((temp.x - 1) - centerTwo.x) < abs(temp.x - centerTwo.x))      // checks if the temp position is to the right of the second room
            temp.x--;                                                         // creates a hallway to the left
        else if (abs((temp.x + 1) - centerTwo.x) < abs(temp.x - centerTwo.x)) // checks if the temp position is to the left of the second room
            temp.x++;                                                         // creates a hallway to the right
        else if (abs((temp.y + 1) - centerTwo.y) < abs(temp.y - centerTwo.y)) // checks if the temp positionis above the second room
            temp.y++;                                                         // creates a hallway downwards
        else if (abs((temp.y - 1) - centerTwo.y) < abs(temp.y - centerTwo.y)) // checks if the temp position is below the second room
            temp.y--;                                                         // creates a hallway upwards
        else                                                                  // if the temp position is the same as the second room
            break;                                                            // stops loop

        map[temp.y][temp.x].ch = '.';           // sets the tiles in the hallway to floor
        map[temp.y][temp.x].walkable = true;    // makes the tiles in the hallway walkable
        map[temp.y][temp.x].transparent = true; // makes the tiles in the hallway transparent
    }
}