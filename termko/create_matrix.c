/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:41:06 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/18 21:23:27 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	**create_rot_z(double angle)
{
	double	**mat;
	int		i;
	int		j;

	check_malloc(mat = (double**)malloc(sizeof(double*) * 4));
	i = 0;
	while (i < 4)
	{
		check_malloc(mat[i] = (double*)malloc(sizeof(double) * 4));
		j = -1;
		while (++j < 4)
			mat[i][j] = (i == j ? 1 : 0);
		i++;
	}
	mat[0][0] = cos(angle);
	mat[1][1] = cos(angle);
	mat[0][1] = -sin(angle);
	mat[1][0] = sin(angle);
	return (mat);
}

double	**create_rot_x(double angle)
{
	double	**mat;
	int		i;
	int		j;

	check_malloc(mat = (double**)malloc(sizeof(double*) * 4));
	i = 0;
	while (i < 4)
	{
		check_malloc(mat[i] = (double*)malloc(sizeof(double) * 4));
		j = -1;
		while (++j < 4)
			mat[i][j] = (i == j ? 1 : 0);
		i++;
	}
	mat[1][1] = cos(angle);
	mat[2][2] = cos(angle);
	mat[1][2] = -sin(angle);
	mat[2][1] = sin(angle);
	return (mat);
}
