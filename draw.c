#include "head.h"

void	draw_line(t_map *fdf, t_coor cr1, t_coor cr2, t_color color)
{
	t_line ln;
	int dx1;
	int dy1;

	// ln.z1 = cr1.z;
	// ln.z2 = cr2.z;
	ln.dx = cr2.x - cr1.x;
	ln.dy = cr2.y - cr1.y;
	dx1 = abs(ln.dx);
	dy1 = abs(ln.dy);
	ln.sx = 2.0 * dy1 - dx1;
	ln.sy = 2.0 * dx1 - dy1;
	// color.curr = color.start;
	if (dy1 <= dx1)
	{
		ln.xs = cr2.x;
		ln.x = cr2.x;
		ln.y = cr2.y;
		ln.xe = cr1.x;
		if (ln.dx >= 0)
		{
			ln.xs = cr1.x;
			ln.x = cr1.x;
			ln.y = cr1.y;
			ln.xe = cr2.x;
		}
		while (ln.x < ln.xe)
		{
			if (!(ln.x + fdf->offx < 0 || ln.x + fdf->offx > HEI || ln.y + fdf->offy < 0 || ln.y + fdf->offy > WID))
				mlx_pixel_put(fdf->mlx, fdf->win, ln.x + fdf->offx, ln.y + fdf->offy, color.curr < 0 ? get_color(&color, ln) : color.curr);
			// color.curr = get_color(&color, ln);
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
		ln.ys = cr2.y;
		ln.x = cr2.x;
		ln.y = cr2.y;
		ln.ye = cr1.y;
		if (ln.dy >= 0)
		{
			ln.ys = cr1.y;
			ln.x = cr1.x;
			ln.y = cr1.y;
			ln.ye = cr2.y;
		}
		while (ln.y < ln.ye)
		{
			
			if (!(ln.x + fdf->offx < 0 || ln.x + fdf->offx > HEI || ln.y + fdf->offy < 0 || ln.y + fdf->offy > WID))
				mlx_pixel_put(fdf->mlx, fdf->win, ln.x + fdf->offx, ln.y + fdf->offy, color.curr < 0 ? get_color(&color, ln) : color.curr);
			// color.curr = get_color(&color, ln);
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
	t_color color;
	int		r;
	int		g;
	int		b;

	cr1.x = (int)map1.x;
	cr1.y = fdf->proj == PARALLEL ? (int)map1.z : (int)map1.y;
	cr2.x = (int)map2.x;
	cr2.y = fdf->proj == PARALLEL ? (int)map2.z : (int)map2.y;
	// printf("distance %d\n", fdf->color.distance);
	// r = ((fdf->color.end >> 16) & 0xFF) - ((fdf->color.start >> 16) & 0xFF);
	// g = ((fdf->color.end >> 8) & 0xFF) - ((fdf->color.start >> 8) & 0xFF);
	// b = (fdf->color.end & 0xFF) - (fdf->color.start & 0xFF); 

	// r = ((fdf->color.start >> 16) & 0xFF) + r * ((map1.z_val - fdf->color.z_min) / fdf->color.distance);
	// g = ((fdf->color.start >> 8) & 0xFF) + g * ((map1.z_val - fdf->color.z_min) / fdf->color.distance);
	// b = (fdf->color.start & 0xFF) + b * ((map1.z_val - fdf->color.z_min) / fdf->color.distance);
	// color.start = (r << 16) | (g << 8) | b;


	// r = ((fdf->color.end >> 16) & 0xFF) - ((fdf->color.start >> 16) & 0xFF);
	// g = ((fdf->color.end >> 8) & 0xFF) - ((fdf->color.start >> 8) & 0xFF);
	// b = (fdf->color.end & 0xFF) - (fdf->color.start & 0xFF); 

	// r = ((fdf->color.start >> 16) & 0xFF) + r * ((map2.z_val - fdf->color.z_min) / fdf->color.distance);
	// g = ((fdf->color.start >> 8) & 0xFF) + g * ((map2.z_val - fdf->color.z_min) / fdf->color.distance);
	// b = (fdf->color.start & 0xFF) + b * ((map2.z_val - fdf->color.z_min) / fdf->color.distance);
	// color.end = (r << 16) | (g << 8) | b;
	color.curr = fdf->color.start;
	draw_line(fdf->full, cr1, cr2, color);
}

void			draw(t_fdf *fdf, void (*projection)(t_3dmap *map, double val, double val2))
{
	int		i;
	int		j;
	t_3dmap	now;
	t_3dmap	next;

	rotate(fdf);
	i = -1;
	while (++i < fdf->full->hei)
	{
		j = -1;
		while (++j < fdf->full->wid)
		{
			now = fdf->map[i][j];
			projection(&now, fdf->r, fdf->siz);
			if (j < fdf->full->wid - 1)
			{
				next = fdf->map[i][j + 1];
				projection(&next, fdf->r, fdf->siz);
							// if (fdf->map[i][j].y == 0.0)
				// printf("x = %f y = %f z = %f\n", fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j].z);
				draw_lines(fdf, now, next);
			}
			if (i < fdf->full->hei - 1)
			{
				next = fdf->map[i + 1][j];
				projection(&next, fdf->r, fdf->siz);
							// if (fdf->map[i][j].y == 0.0)
				// printf("x = %f y = %f z = %f\n", fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j].z);
				draw_lines(fdf, now, next);
			}
		}
	}
}