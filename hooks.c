#include "head.h"

int		key_press(int keykode, t_fdf *fdf)
{
	if (keykode != 19 && keykode != 18 && keykode != 27 && keykode != 24)
		return (0);
	if (keykode == 19)
	{
		// fdf->key.proj = 1;
		fdf->proj = PARALLEL;
		fdf->siz = fdf->prev_siz * 2.1;
		fdf->ang.a_x = 120.0;
		fdf->ang.a_y = 0.0;
		fdf->ang.a_z = 0.0;
		fdf->h_zarr = 1.0;
		clean_main_map(fdf);
		find_min_max(fdf);
	}
	else if (keykode == 18)
	{
		fdf->proj = ISO;
		fdf->siz = fdf->prev_siz;
		fdf->ang.a_x = 0.0;
		fdf->ang.a_y = 0.0;
		fdf->ang.a_z = 0.0;
		clean_main_map(fdf);
	}
	else if ((keykode == 27 || keykode == 24))
	{
		fdf->ang.a_x = fdf->proj ? 120.0 : 0.0;
		fdf->ang.a_y = 0.0;
		fdf->ang.a_z = 0.0;
		fdf->h_zarr *= keykode == 24 ? 1.1 : 0.9;
		if (fdf->h_zarr > 8.0 && fdf->proj == ISO)
			fdf->h_zarr = 8.0;
		else if (fdf->h_zarr > 5.0 && fdf->proj == PARALLEL)
			fdf->h_zarr = 5.0;
		clean_main_map(fdf);
	}
	mlx_clear_window(fdf->full->mlx, fdf->full->win);
	// printf("PROJECTION = %d\n", ISO);
	draw(fdf, fdf->proj ? matrix : set_iso_coords);
	return (0);
}

int		key_release(int keykode, t_fdf *fdf)
{
	t_proj	proj;

	return (0);
}

int		mouse_press(int btn, int x, int y, t_fdf *fdf)
{
	if (x < 0 || x > HEI || y < 0 || y > WID)
		return (1);
	fdf->ang.a_x = 0.0;
	fdf->ang.a_y = 0.0;
	fdf->ang.a_z = 0.0;
	if (btn == 1)
		fdf->ms.left = 1;
	else if ((btn == 4 || btn == 5))
	{
		fdf->siz *= btn == 4 ? 1.1 : 0.9;
		mlx_clear_window(fdf->full->mlx, fdf->full->win);
		draw(fdf, fdf->proj ? matrix : set_iso_coords);
	}
	return (0);
}

int		mouse_release(int btn, int x, int y, t_fdf *fdf)
{
	if (btn == 1)
		fdf->ms.left = 0;
	return (0);
}

int		mouse_move(int x, int y, t_fdf *fdf)
{
	int	prev_x;
	int	prev_y;

	if (x < 0 || x > HEI || y < 0 || y > WID)
		return (1);
	prev_x = fdf->ms.x;
	prev_y = fdf->ms.y;
	fdf->ms.x = x;
	fdf->ms.y = y;
	if (fdf->ms.left == 1)
	{
		fdf->ang.a_y = (double)(y - prev_y) * 0.2;
		fdf->ang.a_x = (double)(x - prev_x) * 0.2;
		fdf->ang.a_z = (double)((x - prev_x) / 2 + (y - prev_y) / 2) * 0.2;
		mlx_clear_window(fdf->full->mlx, fdf->full->win);
		draw(fdf, fdf->proj ? matrix : set_iso_coords);
	}
	return (0);
}
