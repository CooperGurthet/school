// creates a field of view from the player
// http://roguebasin.com/index.php/Simple_Line_of_Sight
#include <rogue.h>

void makeFOV(Entity *player) // creates the fov of the player
{
    int y, x, distance;
    int RADIUS = 15; // radius visible around the player
    Position target; // checks what is in the visible radius

    map[player->pos.y][player->pos.x].visible = true; // sets current position to visible
    map[player->pos.y][player->pos.x].seen = true;    // sets current position to seen

    for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) // iterates through the y values in radius around player
    {
        for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) // iterates through the x values in radius around player
        {
            target.y = y;                                // sets the target y position to y
            target.x = x;                                // sets the target x position to x
            distance = getDistance(player->pos, target); // finds the distance between the player and the target

            if (distance < RADIUS) // checks if the distance is within the radius
            {
                if (isInMap(y, x) && lineOfSight(player->pos, target)) // checks if the target is inbounds and in line of sight
                {
                    map[y][x].visible = true; // sets target position to visible
                    map[y][x].seen = true;    // sets target position to seen
                }
            }
        }
    }
}

void clearFOV(Entity *player) // clears the current visible tiles
{
    int y, x;
    int RADIUS = 15; // radius visible around the player

    for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) // iterates through the y values in radius around player
    {
        for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) // iterates through the x values in radius around player
        {
            if (isInMap(y, x))             // checks if the target is inbounds
                map[y][x].visible = false; // sets the target to not being visible
        }
    }
}

int getDistance(Position origin, Position target) // finds the distance between two points
{
    double dy, dx;
    int distance;
    dx = target.x - origin.x;                      // finds the distance between the x points
    dy = target.y - origin.y;                      // finds the distance between the y points
    distance = floor(sqrt((dx * dx) + (dy * dy))); // trig shit
    // could use fast sqrt function instead
    // remove inverse part of fast inverse sqrt function

    return distance;
}

bool isInMap(int y, int x) // checks if coordinates are in the map or not
{
    if ((0 < y && y < MAP_HEIGHT - 1) && (0 < x && x < MAP_WIDTH - 1)) // checks if y and x are in between 0 and the map height
    {
        return true;
    }

    return false;
}

// don't fully understand this function
bool lineOfSight(Position origin, Position target) // checks if theres anything blocking the line of sight
{
    int t, x, y, abs_delta_x, abs_delta_y, sign_x, sign_y, delta_x, delta_y;

    delta_x = origin.x - target.x; // finds the distance between the two points
    delta_y = origin.y - target.y; // finds the distance between the two points

    abs_delta_x = abs(delta_x); // gets absolute value of delta_x
    abs_delta_y = abs(delta_y); // gets absolute value of delta_y

    sign_x = getSign(delta_x); // checks if delta_x is negative or positive
    sign_y = getSign(delta_y); // checks if delta_y is negative or positive

    x = target.x; // sets x as target.x
    y = target.y; // sets y as target.y

    if (abs_delta_x > abs_delta_y)         // checks if the hypotnuse is x dominant or y dominant
    {                                      // x dominant
        t = abs_delta_y * 2 - abs_delta_x; // twice the absolute of y minus the absolute of x

        do
        {
            if (t >= 0)
            {
                /*if t is greater than or equal to zero then
                 * add the sign of delta_y to y
                 * subtract twice the absolute of delta_x from t   */
                y += sign_y;
                t -= abs_delta_x * 2;
            }
            /* add the sign of delta_x to x
             * add twice the adsolute of delta_y to t  */
            x += sign_x;
            t += abs_delta_y * 2;

            if (x == origin.x && y == origin.y) // checks if the point is at tiles position
            {
                return true; // the tile is in line of sight
            }
        } while (map[y][x].transparent); // continue looping until either reaches the tile position or a wall

        return false; // sight blocked
    }
    else
    {                                      // y dominant
        t = abs_delta_x * 2 - abs_delta_y; // twice the absolute of x minus the absolute of y

        do
        {
            if (t >= 0)
            {
                /*if t is greater than or equal to zero then
                 * add the sign of delta_x to x
                 * subtract twice the absolute of delta_y from t   */
                x += sign_x;
                t -= abs_delta_y * 2;
            }
            /* add the sign of delta_y to y
             * add twice the adsolute of delta_x to t  */
            y += sign_y;
            t += abs_delta_x * 2;

            if (x == origin.x && y == origin.y) // checks if the point is at tiles position
            {
                return true; // the tile is in line of sight
            }
        } while (map[y][x].transparent); // continue looping until either reaches the tile position or a wall

        return false; // sight blocked
    }
}

int getSign(int a) // returns 1 or -1 depending on the sign of the int
{
    return (a < 0) ? -1 : 1;
}