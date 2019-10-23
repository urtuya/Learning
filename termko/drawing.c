/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 21:40:49 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/20 14:52:30 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		draw_x(t_fdf *fdf, t_line *line)
{
	int		x;
	int		y;
	double	eps;
	double	m;
	int		color;

	x = line->x0;
	y = line->y0;
	m = fabsf(1 / line->div);
	eps = m - 1;
	while (x != line->x)
	{
		color = choose_color(line, x, 'x');
		mlx_pixel_put(fdf->mlx->mlx, fdf->mlx->win,\
				x + fdf->offx, y + fdf->offy, color);
		line->x < x ? x-- : x++;
		eps += m;
		if (eps > 0)
		{
			line->y < y ? y-- : y++;
			eps--;
		}
	}
	return (0);
}

int		draw_y(t_fdf *fdf, t_line *line)
{
	int		x;
	int		y;
	double	eps;
	double	m;
	int		color;

	x = line->x0;
	y = line->y0;
	m = fabsf(line->div);
	eps = m - 1;
	while (y != line->y)
	{
		color = choose_color(line, y, 'y');
		mlx_pixel_put(fdf->mlx->mlx, fdf->mlx->win,\
				x + fdf->offx, y + fdf->offy, color);
		line->y < y ? y-- : y++;
		eps += m;
		if (eps > 0)
		{
			line->x < x ? x-- : x++;
			eps--;
		}
	}
	return (0);
}

int		color_returner(t_fdf *fdf, double z)
{
	int red;
	int green;
	int blue;

	red = ((fdf->max_col >> 16) & 0xFF) - ((fdf->min_col >> 16) & 0xFF);
	green = ((fdf->max_col >> 8) & 0xFF) - ((fdf->min_col >> 8) & 0xFF);
	blue = ((fdf->max_col) & 0xFF) - ((fdf->min_col) & 0xFF);
	red = ((fdf->min_col >> 16) & 0xFF) + red * z / fdf->points->minmax;
	green = ((fdf->min_col >> 8) & 0xFF) + green * z / fdf->points->minmax;
	blue = ((fdf->min_col) & 0xFF) + blue * z / fdf->points->minmax;
	return ((red << 16) | (green << 8) | blue);
}

void	putlines_x(t_fdf *fdf)
{
	t_lines	*tmp;

	tmp = fdf->linesx;
	while (tmp)
	{
		fabsf(tmp->line->altjx) < fabsf(tmp->line->altjy) ?\
			draw_y(fdf, tmp->line) : draw_x(fdf, tmp->line);
		tmp = tmp->next;
	}
}

void	putlines_y(t_fdf *fdf)
{
	t_lines	*tmp;

	tmp = fdf->linesy;
	while (tmp)
	{
		fabsf(tmp->line->altjx) < fabsf(tmp->line->altjy) ?\
			draw_y(fdf, tmp->line) : draw_x(fdf, tmp->line);
		tmp = tmp->next;
	}
}
