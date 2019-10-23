#include "head.h"

void	find_min_max(t_fdf *fdf)
{
	int i;
	int j;
	double	last_r;
	double	mn;
	double	mx;

	fdf->last_r = fdf->r;
	mn = fdf->map[0][0].y;
	mx = fdf->map[0][0].y;
	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			mn = fdf->map[i][j].y < mn ? fdf->map[i][j].y : mn;
			mx = fdf->map[i][j].y > mx ? fdf->map[i][j].y : mx;
			j++;
		}
		i++;
	}
	fdf->r = fabs(mn) > fabs(mx) ? fabs(mx) : fabs(mn);
}

void	matrix(t_3dmap *map, double r, double siz)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = map->x;
	prev_y = map->y;
	prev_z = map->z;
	if (r)
	{
		// printf("1: x = %f y = %f z = %f\n", map->x, map->y, map->z);
		map->y = (map->y / r) + 2.1;
		map->x /= map->y;
		map->z /= map->y;
	}
	map->x *= siz;
	map->y *= siz;
	map->z *= siz;
	if (map->x > 2000.0 || map->x <= -2000.0 || map->y > 2000.0 || map->y <= 2000.0)
		printf("z = %f r = %f\n", map->y, r);
	// printf("x = %f y = %f z = %f\n", map->x, map->y, map->z);
}
