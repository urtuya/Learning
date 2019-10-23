/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:48:14 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/20 14:52:03 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	pers_line_x(t_fdf *fdf, int i, int j, t_line *ret)
{
	double	**arrx;
	double	**arrz;
	double	coef;

	coef = fdf->points->coef;
	arrx = fdf->points->arrx;
	arrz = fdf->points->arrz;
	ret->x0 = arrx[i][j] * coef;
	ret->x = arrx[i][j - 1] * coef;
	ret->y0 = -arrz[i][j] * coef;
	ret->y = -arrz[i][j - 1] * coef;
	ret->altjx = ret->x - ret->x0;
	ret->altjy = ret->y - ret->y0;
	ret->div = ret->altjx / ret->altjy;
}

void	pers_line_y(t_fdf *fdf, int i, int j, t_line *ret)
{
	double	**arrx;
	double	**arrz;
	double	coef;

	coef = fdf->points->coef;
	arrx = fdf->points->arrx;
	arrz = fdf->points->arrz;
	ret->x0 = arrx[i][j] * coef;
	ret->x = arrx[i - 1][j] * coef;
	ret->y0 = -arrz[i][j] * coef;
	ret->y = -arrz[i - 1][j] * coef;
	ret->altjx = ret->x - ret->x0;
	ret->altjy = ret->y - ret->y0;
	ret->div = ret->altjx / ret->altjy;
}
