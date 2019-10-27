/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:15:02 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/27 14:15:07 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	find_min_max(t_fdf *fdf)
{
	int			i;
	int			j;
	double		last_r;
	double		mn;
	double		mx;

	fdf->last_r = fdf->r;
	mn = fdf->map[0][0].y;
	mx = fdf->map[0][0].y;
	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			mn = fdf->map[i][j].y < mn ? fdf->map[i][j].y : mn;
			mx = fdf->map[i][j].y > mx ? fdf->map[i][j].y : mx;
			j++;
		}
		i++;
	}
	fdf->r = fabs(mn) > fabs(mx) ? fabs(mx) : fabs(mn);
}

void	matrix(t_3dmap *map, double r, double siz)
{
	if (r)
	{
		map->y = (map->y / r) + map->coef;
		map->x /= map->y;
		map->z /= map->y;
	}
	map->x *= siz;
	map->y *= siz;
	map->z *= siz;
}
