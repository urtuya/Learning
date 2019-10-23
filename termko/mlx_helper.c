/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 02:16:34 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/20 13:18:29 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_fdf	*fdf_malloc(int ac, char **av)
{
	int		fd;
	t_fdf	*fdf;

	if (ac != 2 && ac != 4)
		ft_error("usage: ./fdf <filename> [max_color] [min_color]");
	if ((fd = open(av[1], 'r')) == -1)
		ft_error("File not found.");
	check_malloc(fdf = (t_fdf*)malloc(sizeof(t_fdf)));
	check_malloc(fdf->points = (t_points*)malloc(sizeof(t_points)));
	get_points(fdf, av[1], fd);
	if (ac == 4)
	{
		fdf->max_col = hex_atoi(av[2]);
		fdf->min_col = hex_atoi(av[3]);
	}
	else
	{
		fdf->max_col = 0xA800FF;
		fdf->min_col = 0x1FF2FF;
	}
	return (fdf);
}

void	show_help(t_fdf *fdf)
{
	if (fdf->help)
	{
		if (fdf->project)
			mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1020,\
			0xFFFFFF, "Press 'Shift' to change type of rotation with mouse.");
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1040,\
			0xFFFFFF, "Press 'C' to change type of projection.");
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1060,\
			0xFFFFFF, "Mouse Wheel to zoom in/out.");
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1080,\
			0xFFFFFF, "Right Mouse Button to move.");
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1100,\
			0xFFFFFF, "Left Mouse Button to rotate.");
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1120,\
			0xFFFFFF, "Press 'Enter' to reset the picture.");
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1140,\
			0xFFFFFF, "Press 'R' to turn On/Off the rotation.");
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1160,\
			0xFFFFFF, "Press 'H' to close Help.");
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1180,\
			0xFFFFFF, "Press 'Esc' to close FDF.");
	}
	else
		mlx_string_put(fdf->mlx->mlx, fdf->mlx->win, 10, 1180,\
				0xFFFFFF, "Press 'H' to open Help.");
}

void	recreate_picture(t_fdf *fdf, int flag)
{
	if (flag)
	{
		delete_xyz(fdf);
		free_lines(fdf->linesx);
		free_lines(fdf->linesy);
		fdf->isfirst = 1;
		points_parse(fdf);
	}
	mlx_clear_window(fdf->mlx->mlx, fdf->mlx->win);
	if (fdf->points->width > 1)
	{
		getlines_x(fdf);
		putlines_x(fdf);
	}
	if (fdf->points->length > 1)
	{
		getlines_y(fdf);
		putlines_y(fdf);
	}
	fdf->isfirst = 0;
	show_help(fdf);
}

void	init_constants(t_fdf *fdf)
{
	fdf->points->coef = (fdf->points->length > fdf->points->width ?\
			500 / fdf->points->length : 650 / fdf->points->width);
	if (fdf->points->coef == 0)
		fdf->points->coef = 1;
	fdf->offx = 750;
	fdf->offy = 600;
	fdf->angle = 30;
	fdf->rotate = 0;
	fdf->project = 0;
	fdf->shift = 0;
	fdf->help = 1;
	fdf->isfirst = 1;
}
