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
		hei_count++;
	}
	fdf->full->hei = hei_count;
	close(fd);
}

void			init_zarr(t_fdf *fdf, int fd, char *filename)
{
	char	*line;
	int		i;
	int		j;
	char	**tmp;

	if ((fd = open(filename, O_RDONLY)) < 0)
		exit(1);
	check_malloc(fdf->zarr = (double**)malloc(sizeof(double*)\
					* fdf->full->hei));
	i = 0;
	while (i < fdf->full->hei)
	{
		if (get_next_line(fd, &line) < 0)
			print_error("Error reading map");
		check_malloc(tmp = ft_strsplit(line, ' '));
		check_malloc(fdf->zarr[i] = (double*)malloc(sizeof(double)\
					* fdf->full->wid));
		j = 0;
		while (j < fdf->full->wid)
		{
			fdf->zarr[i][j] = (double)ft_atoi(tmp[j]);
			j++;
		}
		ft_freesplit(tmp);
		i++;
	}
}

double			get_max_z(double **zarr, int hei, int wid)
{
	double	ret;
	double	mn;
	double	mx;
	int		i;
	int		j;

	i = 0;
	mn = zarr[0][0];
	mx = zarr[0][0];
	while (i < hei)
	{
		j = 0;
		while (j < wid)
		{
			mn = zarr[i][j] < mn ? zarr[i][j] : mn;
			mx = zarr[i][j] > mx ? zarr[i][j] : mx;
			j++;
		}
		i++;
	}
	mx = fabs(mx);// / 3.0 * 2.0;
	mn = fabs(mn);// / 3.0 * 2.0;
	return (mx > mn ? mx : mn);
}

void			normalize_z(t_fdf *fdf)
{
	int		i;
	int		j;
	double	zdivisor;

	zdivisor = get_max_z(fdf->zarr, fdf->full->hei, fdf->full->wid);
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

void			init_3dmap(t_fdf *fdf)
{
	int		i;
	int		j;

	check_malloc(fdf->map = (t_3dmap**)malloc(sizeof(t_3dmap*)
												* fdf->full->hei));
	i = 0;
	while (i < fdf->full->hei)
	{
		check_malloc(fdf->map[i] = (t_3dmap*)malloc(sizeof(t_3dmap)
												* fdf->full->wid));
		i++;
	}
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
