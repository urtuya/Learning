#include "head.h"

void	set_iso_coords(t_3dmap *map, double siz)
{
	double	prev_x;
	double	prev_y;
    double  prev_z;

	prev_x = map->x;
	prev_y = map->y;
    prev_z = map->z;
	map->x = ((prev_x - prev_y) * cos(0.523599)) * siz;
	map->y = (-map->z + (prev_x + prev_y) * sin(0.523599)) * siz;
}

void		rotate(t_fdf *fdf)
{
    int		i;
    int		j;

	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			rot_y(&fdf->map[i][j], fdf->ang.a_y);
			rot_x(&fdf->map[i][j], fdf->ang.a_x);
			if (fdf->proj)
				rot_z(&fdf->map[i][j], -fdf->ang.a_x);
			j++;
		}
		i++;
	}
}

void	clean_main_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			fdf->map[i][j].x = (double)(j - fdf->full->y_err);
			fdf->map[i][j].y = (double)(i - fdf->full->x_err);
			fdf->map[i][j].z = fdf->zarr[i][j] * fdf->h_zarr;
			j++;
		}
		i++;
	}
}
