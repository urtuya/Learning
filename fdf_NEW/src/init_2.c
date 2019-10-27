/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:14:51 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/27 14:15:07 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
