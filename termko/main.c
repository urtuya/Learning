/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 06:37:37 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/18 22:28:56 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_fdf	*get_fdf(int ac, char **av)
{
	t_fdf *fdf;

	fdf = fdf_malloc(ac, av);
	map_arr(fdf->points);
	points_parse(fdf);
	init_constants(fdf);
	get_mlx(fdf);
	return (fdf);
}

int		main(int ac, char **av)
{
	t_fdf *fdf;

	fdf = get_fdf(ac, av);
	recreate_picture(fdf, 0);
	mlx_loop(fdf->mlx->mlx);
}
