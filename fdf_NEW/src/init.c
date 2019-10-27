/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:14:54 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/27 14:15:07 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void			init_zarr(t_fdf *fdf, int fd, char *filename)
{
	char	*line;
	int		i;
	int		j;
	char	**tmp;

	if ((fd = open(filename, O_RDONLY)) < 0)
		print_error("Invalid file");
	check_malloc(fdf->zarr = (double**)malloc(sizeof(double*)\
					* fdf->full->hei));
	i = -1;
	while (++i < fdf->full->hei)
	{
		if (get_next_line(fd, &line) < 0)
			print_error("Error reading map");
		check_malloc(tmp = ft_strsplit(line, ' '));
		check_malloc(fdf->zarr[i] = (double*)malloc(sizeof(double)\
					* fdf->full->wid));
		j = -1;
		while (++j < fdf->full->wid)
			fdf->zarr[i][j] = ft_atoi(tmp[j]);
		ft_strdel(&line);
		ft_freesplit(tmp);
	}
}

double			get_max_z(t_fdf *fdf)
{
	double	mn;
	double	mx;
	int		i;
	int		j;

	mn = fdf->zarr[0][0];
	mx = fdf->zarr[0][0];
	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			mn = fdf->zarr[i][j] < mn ? fdf->zarr[i][j] : mn;
			mx = fdf->zarr[i][j] > mx ? fdf->zarr[i][j] : mx;
			j++;
		}
		i++;
	}
	mx = fabs(mx) / 3.0 * 2.0;
	mn = fabs(mn) / 3.0 * 2.0;
	return (mx > mn ? mx : mn);
}

void			normalize_z(t_fdf *fdf)
{
	int		i;
	int		j;
	double	zdivisor;

	zdivisor = get_max_z(fdf);
	if (!zdivisor)
		return ;
	i = 0;
	while (i < fdf->full->hei)
	{
		j = 0;
		while (j < fdf->full->wid)
		{
			fdf->zarr[i][j] /= zdivisor;
			j++;
		}
		i++;
	}
}

static double	get_coef(int hei, int wid)
{
	double	coef;

	coef = hei > wid ? hei / wid : wid / hei;
	if (coef < 2.1)
		coef = 3.1;
	else if (coef <= 5.1)
		coef = 5.1;
	return (coef);
}

void			init_3dmap(t_fdf *fdf)
{
	int		i;
	int		j;
	double	coef;

	coef = get_coef(fdf->full->hei, fdf->full->wid);
	check_malloc(fdf->map = (t_3dmap**)malloc(sizeof(t_3dmap*)\
												* fdf->full->hei));
	i = -1;
	while (++i < fdf->full->hei)
		check_malloc(fdf->map[i] = (t_3dmap*)malloc(sizeof(t_3dmap)\
												* fdf->full->wid));
	i = -1;
	while (++i < fdf->full->hei)
	{
		j = -1;
		while (++j < fdf->full->wid)
		{
			fdf->map[i][j].x = (double)(j - fdf->full->y_err);
			fdf->map[i][j].y = (double)(i - fdf->full->x_err);
			fdf->map[i][j].z = fdf->zarr[i][j] * fdf->h_zarr;
			fdf->map[i][j].coef = coef;
		}
	}
}
