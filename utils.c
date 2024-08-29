// utils will be needed

#include "cub3D.h"

long    deg_to_rad(long deg)
{
    return (deg * (PI / 180));
}

long    rad_to_deg(long rad)
{
    return (rad * (180 / PI));
}

long    distanceAB(int ax, int ay, int bx, int by)
{
    return (sqrt(pow((bx - ax), 2) + pow((by - ay), 2)));
}
