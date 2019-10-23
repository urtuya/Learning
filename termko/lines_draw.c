/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:44:58 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/11 16:52:34 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	lines_x(t_fdf *fdf, int i, int j, t_line *line)
{
	if (!fdf->project)
		iso_line_x(fdf, i, j, line);
	else
		pers_line_x(fdf, i, j, line);
	if (!(fdf->isfirst))
		return ;
	if ((fdf->points->arrz)[i][j] < (fdf->points->arrz)[i][j - 1])
	{
		line->start_col = get_lesser_col(fdf, i, j, 'x');
		line->end_col = get_greater_col(fdf, i, j, 'x');
	}
	else
	{
		line->start_col = get_greater_col(fdf, i, j, 'x');
		line->end_col = get_lesser_col(fdf, i, j, 'x');
	}
}

void	lines_y(t_fdf *fdf, int i, int j, t_line *line)
{
	if (!fdf->project)
		iso_line_y(fdf, i, j, line);
	else
		pers_line_y(fdf, i, j, line);
	if (!(fdf->isfirst))
		return ;
	if ((fdf->points->arrz)[i][j] < (fdf->points->arrz)[i - 1][j])
	{
		line->start_col = get_lesser_col(fdf, i, j, 'y');
		line->end_col = get_greater_col(fdf, i, j, 'y');
	}
	else
	{
		line->start_col = get_greater_col(fdf, i, j, 'y');
		line->end_col = get_lesser_col(fdf, i, j, 'y');
	}
}
