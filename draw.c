#include "head.h"

void	draw_line(t_map *fdf, t_coor cr1, t_coor cr2, int color)
{
	t_line ln;
	int dx1;
	int dy1;
	int xe;
	int ye;

	ln.dx = cr2.x - cr1.x;
	ln.dy = cr2.y - cr1.y;
	dx1 = abs(ln.dx);
	dy1 = abs(ln.dy);
	ln.sx = 2.0 * dy1 - dx1;
	ln.sy = 2.0 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		ln.x = cr2.x;
		ln.y = cr2.y;
		xe = cr1.x;
		if (ln.dx >= 0)
		{
			ln.x = cr1.x;
			ln.y = cr1.y;
			xe = cr2.x;
		}
		while (ln.x < xe)
		{
			if (!(ln.x + fdf->offx < 0 || ln.x + fdf->offx > HEI || ln.y + fdf->offy < 0 || ln.y + fdf->offy > 1000))
				mlx_pixel_put(fdf->mlx, fdf->win, ln.x + fdf->offx, ln.y + fdf->offy, color);

			ln.x++;
			if (ln.sx < 0)
				ln.sx += 2 * dy1;
			else
			{
				if ((ln.dx < 0 && ln.dy < 0) || (ln.dx >0 && ln.dy > 0))
					ln.y++;
				else
					ln.y--;
				ln.sx += 2 * (dy1 - dx1);
			}
		}
	}
	else
	{
		ln.x = cr2.x;
		ln.y = cr2.y;
		ye = cr1.y;
		if (ln.dy >= 0)
		{
			ln.x = cr1.x;
			ln.y = cr1.y;
			ye = cr2.y;
		}
		while (ln.y < ye)
		{
			if (!(ln.x + fdf->offx < 0 || ln.x + fdf->offx > HEI || ln.y + fdf->offy < 0 || ln.y + fdf->offy > 1000))
				mlx_pixel_put(fdf->mlx, fdf->win, ln.x + fdf->offx, ln.y + fdf->offy, color);
			ln.y++;
			if (ln.sy <= 0)
				ln.sy += 2 * dx1;
			else
			{
				if ((ln.dx < 0 && ln.dy < 0) || (ln.dx >0 && ln.dy > 0))
					ln.x++;
				else
					ln.x--;
				ln.sy += 2 * (dx1 - dy1);
			}
		}
	}
}

static void		draw_lines(t_fdf *fdf, t_3dmap map1, t_3dmap map2)
{
	t_coor	cr1;
	t_coor	cr2;
	int		color;

	cr1.x = (int)map1.x;
	cr1.y = (int)map1.y;
	cr2.x = (int)map2.x;
	cr2.y = (int)map2.y;
	color = 0xEE82EE;
	draw_line(fdf->full, cr1, cr2, color);
}

// void			draw(t_fdf *fdf, t_proj proj)
// {
// 	int		i;
// 	int		j;
// 	t_3dmap	now;
// 	t_3dmap	next;

// 	rotate(fdf);
// 	i = 0;
// 	fdf->r = 0.5;
// 	while (i < fdf->full->hei)
// 	{
// 		j = 0;
// 		while (j < fdf->full->wid)
// 		{
// 			now = fdf->map[i][j];
// 			proj == ISO ? set_iso_coords(&now, fdf->siz, fdf->h_zarr) :
// 							matrix(&now, fdf->r, fdf->siz);
// 			if (j < fdf->full->wid - 1)
// 			{
// 				next = fdf->map[i][j + 1];
// 				proj == ISO ? set_iso_coords(&next, fdf->siz, fdf->h_zarr) : 
// 							matrix(&next, fdf->r, fdf->siz);
// 				draw_lines(fdf, now, next);
// 			}
// 			if (i < fdf->full->hei - 1)
// 			{
// 				next = fdf->map[i + 1][j];
// 				proj == ISO ? set_iso_coords(&next, fdf->siz, fdf->h_zarr) : 
// 								matrix(&next, fdf->r, fdf->siz);
// 				draw_lines(fdf, now, next);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void			draw(t_fdf *fdf)
{
	int		i;
	int		j;
	t_3dmap	now;
	t_3dmap	next;

	rotate(fdf);
	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			now = fdf->map[i][j];
			set_iso_coords(&now, fdf->siz, fdf->h_zarr);
			if (j < fdf->full->wid - 1)
			{
				next = fdf->map[i][j + 1];
				set_iso_coords(&next, fdf->siz, fdf->h_zarr);
				draw_lines(fdf, now, next);
			}
			if (i < fdf->full->hei - 1)
			{
				next = fdf->map[i + 1][j];
				set_iso_coords(&next, fdf->siz, fdf->h_zarr);
				draw_lines(fdf, now, next);
			}
			j++;
		}
		i++;
	}
}