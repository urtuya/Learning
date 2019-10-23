/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:13:53 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/19 16:56:06 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	fill_arr(t_fdf *fdf, char **lines)
{
	char	**tmp;
	int		i;
	int		j;
	int		check;

	i = -1;
	check = 0;
	while (++i < fdf->points->length)
	{
		check_malloc(tmp = ft_strsplit(lines[i], ' '));
		fdf->points->width = ft_count(tmp);
		if (check != 0 && check != fdf->points->width)
			ft_error("Found wrong line length. Exiting.");
		check = fdf->points->width;
		check_malloc((fdf->points->array[i] = (double*)malloc(sizeof(double)\
						* fdf->points->width)));
		j = -1;
		while (++j < fdf->points->width)
			fdf->points->array[i][j] = ft_atoi(tmp[j]);
		free_tmp(tmp);
		free(tmp);
	}
}

void	get_points(t_fdf *fdf, char *file, int fd)
{
	int		i;
	int		len;
	char	*str;
	char	**split;

	len = get_length(fdf, fd);
	check_malloc(str = (char*)malloc(sizeof(char) * len));
	check_malloc(fdf->points->array = (double**)malloc(sizeof(double*)\
				* (fdf->points->length + 1)));
	fill_str(file, str);
	check_malloc(split = ft_strsplit(str, '\n'));
	fill_arr(fdf, split);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	free(str);
}

void	map_arr(t_points *str)
{
	int	i;
	int	j;
	int	max;
	int	min;

	i = 0;
	max = (str->array)[0][0];
	min = (str->array)[0][0];
	while (i < str->length)
	{
		j = 0;
		while (j < str->width)
		{
			max = (max < (str->array)[i][j] ? (str->array)[i][j] : max);
			min = (min > (str->array)[i][j] ? (str->array)[i][j] : min);
			j++;
		}
		i++;
	}
	str->minmax = max - min;
	str->min_height = min;
	str->max_height = max;
}

void	create_arrays(t_fdf *fdf, int length, int width)
{
	int		i;

	check_malloc(fdf->points->arrx =\
			(double**)malloc(sizeof(double*) * length));
	check_malloc(fdf->points->arry =\
			(double**)malloc(sizeof(double*) * length));
	check_malloc(fdf->points->arrz =\
			(double**)malloc(sizeof(double*) * length));
	i = 0;
	while (i < length)
	{
		check_malloc(fdf->points->arrx[i] =\
				(double*)malloc(sizeof(double) * width));
		check_malloc(fdf->points->arry[i] =\
				(double*)malloc(sizeof(double) * width));
		check_malloc(fdf->points->arrz[i] =\
				(double*)malloc(sizeof(double) * width));
		i++;
	}
}

void	points_parse(t_fdf *fdf)
{
	int i;
	int j;
	int length;
	int width;

	i = -1;
	length = fdf->points->length;
	width = fdf->points->width;
	create_arrays(fdf, length, width);
	while (++i < length)
	{
		j = -1;
		while (++j < width)
		{
			(fdf->points->arrx)[i][j] = j;
			(fdf->points->arry)[i][j] = i;
			(fdf->points->arrz)[i][j] = (fdf->points->array)[i][j];
		}
	}
	normalize_arr(fdf->points);
}
