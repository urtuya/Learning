/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:14:42 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/27 14:15:07 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	draw_line(t_map *fdf, t_coor cr1, t_coor cr2, int color)
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
	cr1.y = fdf->proj == PARALLEL ? (int)map1.z : (int)map1.y;
	cr2.x = (int)map2.x;
	cr2.y = fdf->proj == PARALLEL ? (int)map2.z : (int)map2.y;
	color = fdf->color;
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
				draw_lines(fdf, now, next);
			}
			if (i < fdf->full->hei - 1)
			{
				next = fdf->map[i + 1][j];
				projection(&next, fdf->r, fdf->siz);
				draw_lines(fdf, now, next);
			}
		}
	}
}