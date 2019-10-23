/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:01:47 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/21 18:06:01 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_matrix(double **mat)
{
	int i;

	i = 0;
	while (i < 4)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

void	help_normalize(t_fdf *fdf, double max)
{
	int		i;
	int		j;

	if (!max)
		return ;
	i = 0;
	while (i < fdf->points->length)
	{
		j = 0;
		while (j < fdf->points->width)
		{
			fdf->points->arry[i][j] = (fdf->points->arry[i][j] / max) + 1.1;
			if (fdf->points->arry[i][j])
			{
				fdf->points->arrx[i][j] /= fdf->points->arry[i][j];
				fdf->points->arrz[i][j] /= fdf->points->arry[i][j];
			}
			fdf->normal = 1;
			j++;
		}
		i++;
	}
}

void	normalize_y(t_fdf *fdf)
{
	int		i;
	int		j;
	double	min;
	double	max;

	min = fdf->points->arry[0][0];
	max = fdf->points->arry[0][0];
	i = 0;
	while (i < fdf->points->length)
	{
		j = 0;
		while (j < fdf->points->width)
		{
			if (fdf->points->arry[i][j] < min)
				min = fdf->points->arry[i][j];
			if (fdf->points->arry[i][j] > max)
				max = fdf->points->arry[i][j];
			j++;
		}
		i++;
	}
	if (fabs(min) > fabs(max))
		help_normalize(fdf, fabs(min));
	else
		help_normalize(fdf, fabs(max));
}

void	mult_matrix(t_fdf *fdf, double **mat2, int w)
{
	int		i;
	int		j;
	double	x;
	double	y;
	double	z;

	i = 0;
	while (i < fdf->points->length)
	{
		j = 0;
		while (j < fdf->points->width)
		{
			x = fdf->points->arrx[i][j];
			y = fdf->points->arry[i][j];
			z = fdf->points->arrz[i][j];
			fdf->points->arrx[i][j] = x * mat2[0][0] + y * mat2[0][1] +\
										z * mat2[0][2] + w * mat2[0][3];
			fdf->points->arry[i][j] = x * mat2[1][0] + y * mat2[1][1] +\
										z * mat2[1][2] + w * mat2[0][3];
			fdf->points->arrz[i][j] = x * mat2[2][0] + y * mat2[2][1] +\
										z * mat2[2][2] + w * mat2[2][3];
			j++;
		}
		i++;
	}
}
