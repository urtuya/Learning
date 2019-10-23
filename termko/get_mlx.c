/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 06:32:34 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/18 19:10:07 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	delete_xyz(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->points->length)
	{
		free((fdf->points->arrx)[i]);
		free((fdf->points->arry)[i]);
		free((fdf->points->arrz)[i]);
		i++;
	}
	free(fdf->points->arrx);
	free(fdf->points->arry);
	free(fdf->points->arrz);
	fdf->points->arrx = NULL;
	fdf->points->arry = NULL;
	fdf->points->arrz = NULL;
}

void	get_mlx(t_fdf *fdf)
{
	if (!(fdf->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_error("Unexpected error with malloc.");
	fdf->mlx->mlx = mlx_init();
	fdf->mlx->win = mlx_new_window(fdf->mlx->mlx, 1500, 1200, "FDF");
	fdf->mouse = 0;
	mlx_key_hook(fdf->mlx->win, key_hook, fdf);
	mlx_loop_hook(fdf->mlx->mlx, loop_hook, fdf);
	mlx_hook(fdf->mlx->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->mlx->win, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->mlx->win, 6, 0, mouse_move, fdf);
	check_malloc(fdf->linesx = (t_lines*)malloc(sizeof(t_lines)));
	check_malloc(fdf->linesy = (t_lines*)malloc(sizeof(t_lines)));
}
