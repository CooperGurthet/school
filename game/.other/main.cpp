/**
 * TODO: inventory
 * TODO: enemies
 * TODO: items
 * TODO: map
 * TODO: replace install of pdcurses with unicode version
 */

/**
 * Bosses:
 *  Golem- Wake it up and have it attack
 *  Dragon?
 *
 */

#include <curses.h>
#include <tuple>

int dx, dy;
int loop = 1;
int maxX, maxY;
int i = 0;

class entity
{
public:
    char character;
    int color;
    int x;
    int y;
};

class object
{
public:
    char symbol;
    int color;
    int x;
    int y;
    bool walkable;
};

int screenSetup() // starting the window
{
    initscr();   // initializes curse mode
    noecho();    // turns off echo
    curs_set(0); // removes the flashing cursor
    return 0;
}

int map() // making the map
{
    /**
     * algorithm
     * http://roguebasin.com/?title=Dungeon-Building_Algorithm
     *
     * 1. Fill the whole map with solid earth
     * 2. Dig out a single room in the centre of the map
     * 3. Pick a wall of any room
     * 4. Decide upon a new feature to build
     * 5. See if there is room to add the new feature through the chosen wall
     * 6. If yes, continue. If no, go back to step 3
     * 7. Add the feature through the chosen wall
     * 8. Go back to step 3, until the dungeon is complete
     * 9. Add the up and down staircases at random points in map
     * 10. Finally, sprinkle some monsters and items liberally over dungeon
     *
     **/
    // clear(); //clears current map and increments current floor

    // fill map with solid
    int size = maxX * maxY;
    for (int i = 0; i < size; ++i)
    {
        object wall[i];
        wall[i].symbol = '#';
        wall[i].x = (i / maxY);
        wall[i].y = (i / maxX);
        wall[i].walkable = false;
        mvaddch(wall[i].y, wall[i].x, wall[i].symbol);
    }
}

int movement(entity ent, int &dx, int &dy) // movement function
{
    if ((maxX > ent.x + dx) && (dx != 0) && (ent.x + dx > 0)) // check if movement is allowed
    {
        ent.x = ent.x + dx;
        return ent.x;
    }
    else if (dx != 0)
    {
        return ent.x;
    }

    if ((maxY > ent.y + dy) && (dy != 0) && (ent.y + dy > 0))
    {
        ent.y = ent.y + dy;
        return ent.y;
    }
    else if (dy != 0)
    {
        return ent.y;
    }
}

int main(void)
{
    entity player;
    player.x = 10;
    player.y = 6;
    player.character = '@';

    screenSetup(); // initializes the screen
    maxX = getmaxx(stdscr);
    maxY = getmaxy(stdscr);
    // map();
    while (loop) // while game is running do these things
    {

        mvprintw(8, 0, "%d", player.x);
        mvprintw(9, 0, "%d", player.y);

        // mvprintw(3, 0, "%d", maxX);
        // mvprintw(4, 0, "%d", maxY);

        // mvprintw(0, 0, "%d", player.x);
        // mvprintw(1, 0, "%d", player.y);

        mvaddch(player.y, player.x, player.character); // draw the character at the y,x coordinates

        switch (getch())
        {
        case 'q': // stops game by stopping loop
            loop = 0;
            break;
        // normal wasd controls to move character in corresponding direction

        // TODO: change the borders to anything not walkable
        case 'd':
            mvaddch(player.y, player.x, ' '); // clears old character
            dx = 1;
            dy = 0;
            player.x = movement(player, dx, dy);
            break;
        case 'a':
            mvaddch(player.y, player.x, ' '); // clears old character
            dx = -1;
            dy = 0;
            player.x = movement(player, dx, dy);
            break;
        case 'w':
            mvaddch(player.y, player.x, ' '); // clears old character
            dx = 0;
            dy = -1;
            player.y = movement(player, dx, dy);
            break;
        case 's':
            mvaddch(player.y, player.x, ' '); // clears old character
            dx = 0;
            dy = 1;
            player.y = movement(player, dx, dy);
            break;
        default:
            break;
        }
    }
    endwin(); // stops from being in curse mode(stops game)
    return 0;
}