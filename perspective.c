#include "head.h"

void	find_min_max(t_fdf *fdf)
{
	int i;
	int j;
	double	mn;
	double	mx;

	// printf("tut\n");
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
	// printf("r = %f\n", fdf->r);
}

void	matrix(t_3dmap *map, double r, double siz/*t_fdf *fdf*/)
{
	// int i;
	// int j;

	// i = 0;
	// if (!fdf->r)
	// 	return ;
	// while (i < fdf->full->hei)
	// {
	// 	j = 0;
	// 	while (j < fdf->full->wid)
	// 	{
	// 		// rot_x(&fdf->map[i][j], 30);
	// 		fdf->map[i][j].y = fdf->map[i][j].y / fdf->r + 1.1;
	// 		if (fdf->map[i][j].y)
	// 		{
	// 			fdf->map[i][j].x /= fdf->map[i][j].y;
	// 			fdf->map[i][j].z /= fdf->map[i][j].y;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// rot_x(map, 3000);
	if (r)
	{
		map->y = (map->y / r) + 2.1;
		if (map->y)
		{
			map->x /= map->y;
			map->z /= map->y;
		}
	}
	map->x *= siz;
	map->y *= siz;
	map->z *= siz;
	// rot_x(map, 120);
	

	printf("x = %f y = %f z = %f\n", map->x, map->y, map->z);
}


static void	draw_lines(t_fdf *fdf, t_3dmap map1, t_3dmap map2)
{
	t_coor	cr1;
	t_coor	cr2;
	int		color;

	cr1.x = (int)(map1.x * fdf->siz);
	cr1.y = (int)(map1.z * fdf->siz);
	cr2.x = (int)(map2.x * fdf->siz);
	cr2.y = (int)(map2.z * fdf->siz);
	color = 0xEE82EE;
	draw_line(fdf->full, cr1, cr2, color);
	// printf("x1 = %d y1 = %d\n", cr1.x, cr1.y);
	// printf("x2 = %d y2 = %d\n", cr2.x, cr2.y);
}

void	draw2(t_fdf *fdf)
{
	int i;
	int j;
	t_3dmap	now;
	t_3dmap	next;
	int		flag;

	flag = 0;
	i = 0;
	// clean_main_map(fdf);
	// find_min_max(fdf);
	// matrix(fdf);
	rotate(fdf);
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			now = fdf->map[i][j];
			// rot_y(&now, 30);
			matrix(&now, fdf->r, fdf->siz);
			// rot_x(&now, 30);
			if (j < fdf->full->wid - 1)
			{
				next = fdf->map[i][j + 1];
				// rot_y(&next, 30);
				matrix(&next, fdf->r, fdf->siz);
				// rot_x(&next, 30);
				draw_lines(fdf, now, next);
			}
			if (i < fdf->full->hei - 1)
			{
				next = fdf->map[i + 1][j];
				// rot_y(&next, 30);
				matrix(&next, fdf->r, fdf->siz);
				// rot_x(&next, 30);
				draw_lines(fdf, now, next);
			}
			j++;
		}
		i++;
	}
}
