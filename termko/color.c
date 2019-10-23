/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:30:55 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/18 21:22:39 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		choose_color(t_line *line, int current, char axis)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	if (line->start_col == line->end_col)
		return (line->end_col);
	if (axis == 'x')
		percentage = percent(line->x0, line->x, current);
	else
		percentage = percent(line->y0, line->y, current);
	red = (line->start_col >> 16) & 0xFF;
	red = get_light(red, (line->end_col >> 16) & 0xFF, percentage);
	green = (line->start_col >> 8) & 0xFF;
	green = get_light(green, (line->end_col >> 8) & 0xFF, percentage);
	blue = line->start_col & 0xFF;
	blue = get_light(blue, line->end_col & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int		get_greater_col(t_fdf *fdf, int i, int j, char axis)
{
	double	z;

	if (fdf->points->max_height == fdf->points->min_height)
		return (fdf->max_col);
	if (axis == 'x')
	{
		if ((fdf->points->array)[i][j - 1] > (fdf->points->array)[i][j])
			z = (fdf->points->array)[i][j - 1];
		else
			z = (fdf->points->array)[i][j];
	}
	else
	{
		if ((fdf->points->array)[i - 1][j] > (fdf->points->array)[i][j])
			z = (fdf->points->array)[i - 1][j];
		else
			z = (fdf->points->array)[i][j];
	}
	z -= fdf->points->min_height;
	return (color_returner(fdf, z));
}

int		get_lesser_col(t_fdf *fdf, int i, int j, char axis)
{
	double	z;

	if (fdf->points->max_height == fdf->points->min_height)
		return (fdf->min_col);
	if (axis == 'x')
	{
		if ((fdf->points->array)[i][j - 1] < (fdf->points->array)[i][j])
			z = (fdf->points->array)[i][j - 1];
		else
			z = (fdf->points->array)[i][j];
	}
	else
	{
		if ((fdf->points->array)[i - 1][j] < (fdf->points->array)[i][j])
			z = (fdf->points->array)[i - 1][j];
		else
			z = (fdf->points->array)[i][j];
	}
	z -= fdf->points->min_height;
	return (color_returner(fdf, z));
}
