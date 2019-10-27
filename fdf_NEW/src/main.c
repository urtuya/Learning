/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:14:59 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/27 14:15:07 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void		print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

void		check_malloc(void *data)
{
	if (!data)
		print_error("malloc error");
}

void		init_mouse_keys(t_fdf *fdf)
{
	fdf->ms.left = 0;
	fdf->ms.x = 0;
	fdf->ms.y = 0;
	fdf->key.h_key = 0;
	fdf->key.anykey_ispressed = 0;
}

static void	set_off(t_fdf *fdf)
{
	double	a;
	double	b;

	fdf->h_zarr = 1.0;
	fdf->siz = 1.0;
	fdf->full->offx = HEI / 2;
	fdf->full->offy = WID / 2;
	a = WID / fdf->full->wid / 2;
	b = HEI / fdf->full->hei / 2;
	fdf->siz = a < b ? a : b;
	fdf->siz = !fdf->siz ? 1 : fdf->siz;
	fdf->prev_siz = fdf->siz;
	fdf->ang.a_x = 0.0;
	fdf->ang.a_y = 0.0;
	fdf->ang.a_z = 0.0;
	fdf->full->x_err = fdf->full->hei / 2;
	fdf->full->y_err = fdf->full->wid / 2;
	fdf->color = 0x9933FF;
}

t_fdf		*init_fdf(char *filename)
{
	t_fdf	*fdf;
	int		fd;

	check_malloc(fdf = (t_fdf*)malloc(sizeof(t_fdf)));
	check_malloc(fdf->full = (t_map*)malloc(sizeof(t_map)));
	fdf->full->wid = 0;
	fdf->full->hei = 0;
	fdf->zarr = NULL;
	fdf->map = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		print_error("Error open file");
	read_map(fdf, fd);
	init_zarr(fdf, fd, filename);
	normalize_z(fdf);
	set_off(fdf);
	init_3dmap(fdf);
	init_mouse_keys(fdf);
	fdf->full->mlx = mlx_init();
	fdf->full->win = mlx_new_window(fdf->full->mlx, HEI, WID, "FdF");
	return (fdf);
}

void		apply_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->full->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->full->win, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->full->win, 6, 0, mouse_move, fdf);
	mlx_hook(fdf->full->win, 2, 0, key_press, fdf);
}

int			main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = NULL;
	if (argc != 2)
		print_error("USAGE");
	fdf = init_fdf(argv[1]);
	draw(fdf, fdf->proj == PARALLEL ? matrix : set_iso_coords);
	apply_hooks(fdf);
	mlx_loop(fdf->full->mlx);
	return (0);
}
