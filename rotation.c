#include "head.h"

double  degtorad(double deg)
{
    return (deg * M_PI / 180);
}

void rot_x(t_3dmap *map, double angle)
{
    double  prev_y;
    double  prev_z;

    prev_y = map->y;
    prev_z = map->z;
    map->y = prev_y * cos(degtorad(angle)) - prev_z * sin(degtorad(angle));
    map->z = prev_y * sin(degtorad(angle)) + prev_z * cos(degtorad(angle));
}

void rot_y(t_3dmap *map, double angle)
{
    double  prev_x;
    double  prev_z;

    prev_x = map->x;
    prev_z = map->z;
    map->x = prev_x * cos(degtorad(angle)) + prev_z * sin(degtorad(angle));
    map->z = -prev_x * sin(degtorad(angle)) + prev_z * cos(degtorad(angle));
}

void rot_z(t_3dmap *map, double angle)
{
    double  prev_x;
    double  prev_y;

    prev_x = map->x;
    prev_y = map->y;
    map->x = prev_x * cos(degtorad(angle)) + prev_y * sin(degtorad(angle));
    map->y = -prev_x * sin(degtorad(angle)) + prev_y * cos(degtorad(angle));
}