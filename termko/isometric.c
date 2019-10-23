/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:09:12 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/20 14:50:42 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	iso_line_x(t_fdf *fdf, int i, int j, t_line *ret)
{
	double	**arrx;
	double	**arry;
	double	**arrz;
	double	coef;
	double	rad;

	coef = fdf->points->coef;
	rad = fdf->angle * M_PI / 180;
	arrx = fdf->points->arrx;
	arry = fdf->points->arry;
	arrz = fdf->points->arrz;
	ret->x0 = (arrx[i][j] - arry[i][j]) * cos(rad) * coef;
	ret->x = (arrx[i][j - 1] - arry[i][j - 1]) * cos(rad) * coef;
	ret->y0 = (-arrz[i][j] + (arrx[i][j] +\
				arry[i][j]) * sin(rad)) * coef;
	ret->y = (-arrz[i][j - 1] + (arrx[i][j - 1] +\
				arry[i][j - 1]) * sin(rad)) * coef;
	ret->altjx = ret->x - ret->x0;
	ret->altjy = ret->y - ret->y0;
	ret->div = ret->altjx / ret->altjy;
}

void	iso_line_y(t_fdf *fdf, int i, int j, t_line *ret)
{
	double	**arrx;
	double	**arry;
	double	**arrz;
	double	coef;
	double	rad;

	coef = fdf->points->coef;
	rad = fdf->angle * M_PI / 180;
	arrx = fdf->points->arrx;
	arry = fdf->points->arry;
	arrz = fdf->points->arrz;
	ret->x0 = (arrx[i][j] - arry[i][j]) * cos(rad) * coef;
	ret->x = (arrx[i - 1][j] - arry[i - 1][j]) * cos(rad) * coef;
	ret->y0 = (-arrz[i][j] + (arrx[i][j] +\
				arry[i][j]) * sin(rad)) * coef;
	ret->y = (-arrz[i - 1][j] + (arrx[i - 1][j] +\
				arry[i - 1][j]) * sin(rad)) * coef;
	ret->altjx = ret->x - ret->x0;
	ret->altjy = ret->y - ret->y0;
	ret->div = ret->altjx / ret->altjy;
}
