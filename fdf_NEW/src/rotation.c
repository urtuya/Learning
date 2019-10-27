/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:15:05 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/27 14:15:07 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static double	degtorad(double deg)
{
	return (deg * M_PI / 180);
}

void			rot_x(t_3dmap *map, double angle)
{
	double	prev_y;
	double	prev_z;

	prev_y = map->y;
	prev_z = map->z;
	map->y = prev_y * cos(degtorad(angle)) - prev_z * sin(degtorad(angle));
	map->z = prev_y * sin(degtorad(angle)) + prev_z * cos(degtorad(angle));
}

static void		rot_y(t_3dmap *map, double angle)
{
	double	prev_x;
	double	prev_z;

	prev_x = map->x;
	prev_z = map->z;
	map->x = prev_x * cos(degtorad(angle)) + prev_z * sin(degtorad(angle));
	map->z = -prev_x * sin(degtorad(angle)) + prev_z * cos(degtorad(angle));
}

static void		rot_z(t_3dmap *map, double angle)
{
	double	prev_x;
	double	prev_y;

	prev_x = map->x;
	prev_y = map->y;
	map->x = prev_x * cos(degtorad(angle)) + prev_y * sin(degtorad(angle));
	map->y = -prev_x * sin(degtorad(angle)) + prev_y * cos(degtorad(angle));
}

void			rotate(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			rot_y(&fdf->map[i][j], fdf->ang.a_y);
			rot_x(&fdf->map[i][j], fdf->ang.a_x);
			rot_z(&fdf->map[i][j], fdf->ang.a_z);
			j++;
		}
		i++;
	}
}
