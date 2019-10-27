#include "head.h"

static void		check_valid(t_fdf *fdf, char *line)
{
	int		i;
	int		wid_count;
	char	**tmp;
	int		j;

	if (!line && !*line)
		print_error("Error while reading map");
	check_malloc(tmp = ft_strsplit(line, ' '));
	i = 0;
	while (tmp[i])
		i++;
	if (!fdf->full->wid)
		fdf->full->wid = i;
	else if (fdf->full->wid != i)
		print_error("map error");
	ft_freesplit(tmp);
}

void			read_map(t_fdf *fdf, int fd)
{
	char	*line;
	int		hei_count;

	hei_count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		check_valid(fdf, line);
		ft_strdel(&line);
		hei_count++;
	}
	fdf->full->hei = hei_count;
	close(fd);
}

void			init_static_z(t_fdf *fdf, int fd, char *filename)
{
	char	*line;
	int		i;
	int		j;
	char	**tmp;

	if ((fd = open(filename, O_RDONLY)) < 0)
		print_error("Invalid file");
	check_malloc(fdf->static_z = (int**)malloc(sizeof(int*)\
					* fdf->full->hei));
	i = -1;
	while (++i < fdf->full->hei)
	{
		if (get_next_line(fd, &line) < 0)
			print_error("Error reading map");
		check_malloc(tmp = ft_strsplit(line, ' '));
		check_malloc(fdf->static_z[i] = (int*)malloc(sizeof(int)\
					* fdf->full->wid));
		j = -1;
		while (++j < fdf->full->wid)
			fdf->static_z[i][j] = ft_atoi(tmp[j]);
		ft_strdel(&line);
		ft_freesplit(tmp);
	}
}

void			init_zarr(t_fdf *fdf, int fd, char *filename)
{
	int		i;
	int		j;
	double	mn;
	double	mx;

	mn = (double)fdf->static_z[0][0];
	mx = (double)fdf->static_z[0][0];
	check_malloc(fdf->zarr = (double**)malloc(sizeof(double*)\
					* fdf->full->hei));
	i = -1;
	while (++i < fdf->full->hei)
	{
		check_malloc(fdf->zarr[i] = (double*)malloc(sizeof(double)\
					* fdf->full->wid));
		j = -1;
		while (++j < fdf->full->wid)
			fdf->zarr[i][j] = (double)fdf->static_z[i][j];
	}
	// fdf->color.z_max = fdf->static_z[0][0];
	// fdf->color.z_min = fdf->static_z[0][0];
}

double			get_max_z(t_fdf *fdf)//double **zarr, int hei, int wid, t_color *color)
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
	fdf->color.z_max = (int)mx;
	fdf->color.z_min = (int)mn;
	fdf->color.distance = fdf->color.z_max - fdf->color.z_min;
	// printf("zmax = %d\n", fdf->color.z_max);
	// printf("mzin = %d\n", fdf->color.z_min);
	// exit(0);
	mx = fabs(mx) / 3.0 * 2.0;
	mn = fabs(mn) / 3.0 * 2.0;
	return (mx > mn ? mx : mn);
}

void			normalize_z(t_fdf *fdf)
{
	int		i;
	int		j;
	double	zdivisor;

	zdivisor = get_max_z(fdf);//fdf->zarr, fdf->full->hei, fdf->full->wid, &fdf->color);
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
	// fdf->color.z_max /= zdivisor;
	// fdf->color.z_min /= zdivisor;
	// fdf->color.distance = fdf->color.z_max - fdf->color.z_min;
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
			fdf->map[i][j].z_val = fdf->static_z[i][j];
			fdf->map[i][j].coef = coef;
		}
	}
}
