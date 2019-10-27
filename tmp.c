#include "head.h"

void	init_line(t_line *ln, t_coor cr1, t_coor cr2, t_color *color)
{
	ln->dx = cr2.x - cr1.x;
	ln->dy = cr2.y - cr1.y;
	ln->dx1 = abs(ln->dx);
	ln->dy1 = abs(ln->dy);
	ln->sx = 2.0 * ln->dy1 - ln->dx1;
	ln->sy = 2.0 * ln->dx1 - ln->dy1;
	color->curr = color->start;
}

void	set_values_x(t_line *ln, t_coor cr1, t_coor cr2)
{
	if (ln->dx >= 0)
	{
		ln->xs = cr1.x;
		ln->x = cr1.x;
		ln->y = cr1.y;
		ln->xe = cr2.x;
	}
	else
	{
		ln->xs = cr2.x;
		ln->x = cr2.x;
		ln->y = cr2.y;
		ln->xe = cr1.x;
	}
}

void	set_values_y(t_line *ln, t_coor cr1, t_coor cr2)
{
	if (ln->dy >= 0)
	{
		ln->ys = cr1.y;
		ln->x = cr1.x;
		ln->y = cr1.y;
		ln->ye = cr2.y;
	}
	else
	{
		ln->ys = cr2.y;
		ln->x = cr2.x;
		ln->y = cr2.y;
		ln->ye = cr1.y;
	}
}

void	draw_line(t_map *fdf, t_coor cr1, t_coor cr2, t_color color)
{
	t_line ln;
	int dx1;
	int dy1;

	ln.dx = cr2.x - cr1.x;
	ln.dy = cr2.y - cr1.y;
	dx1 = abs(ln.dx);
	dy1 = abs(ln.dy);
	ln.sx = 2.0 * dy1 - dx1;
	ln.sy = 2.0 * dx1 - dy1;
	// color.curr = color.start;
	color.curr = 0xB266FF;
	// init_line(&ln, cr1, cr2, &color);
	if (ln.dy1 <= ln.dx1)
	{
		// set_values_x(&ln, cr1, cr2);
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
				mlx_pixel_put(fdf->mlx, fdf->win, ln.x + fdf->offx, ln.y + fdf->offy, color.curr/*get_color(&color, ln)*/);
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
		// set_values_y(&ln, cr1, cr2);
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
				mlx_pixel_put(fdf->mlx, fdf->win, ln.x + fdf->offx, ln.y + fdf->offy, color.curr/*get_color(&color, ln)*/);
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