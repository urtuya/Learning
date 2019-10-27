/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:14:57 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/27 14:15:07 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	set_iso_coords(t_3dmap *map, double h_zarr, double siz)
{
	double	prev_x;
	double	prev_y;

	(void)h_zarr;
	prev_x = map->x;
	prev_y = map->y;
	map->x = ((prev_x - prev_y) * cos(0.523599)) * siz;
	map->y = (-map->z + (prev_x + prev_y) * sin(0.523599)) * siz;
}

void	clean_main_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			fdf->map[i][j].x = (double)(j - fdf->full->y_err);
			fdf->map[i][j].y = (double)(i - fdf->full->x_err);
			fdf->map[i][j].z = fdf->zarr[i][j] * fdf->h_zarr;
			j++;
		}
		i++;
	}
}
