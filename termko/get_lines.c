/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:38:55 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/11 17:00:31 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	getlines_x(t_fdf *fdf)
{
	int		i;
	int		j;
	t_lines	*tmp;

	tmp = fdf->linesx;
	i = fdf->points->length - 1;
	while (i >= 0)
	{
		j = fdf->points->width - 1;
		while (j > 0)
		{
			if (fdf->isfirst)
				check_malloc(tmp->line = (t_line*)malloc(sizeof(t_line)));
			lines_x(fdf, i, j, tmp->line);
			if (j - 1 <= 0 && i - 1 < 0)
				break ;
			if (fdf->isfirst)
				check_malloc(tmp->next = (t_lines*)malloc(sizeof(t_lines)));
			tmp = tmp->next;
			j--;
		}
		i--;
	}
	tmp->next = NULL;
}

void	getlines_y(t_fdf *fdf)
{
	int		i;
	int		j;
	t_lines	*tmp;

	tmp = fdf->linesy;
	i = fdf->points->length - 1;
	while (i > 0)
	{
		j = fdf->points->width - 1;
		while (j >= 0)
		{
			if (fdf->isfirst)
				check_malloc(tmp->line = (t_line*)malloc(sizeof(t_line)));
			lines_y(fdf, i, j, tmp->line);
			if (j - 1 < 0 && i - 1 <= 0)
				break ;
			if (fdf->isfirst)
				check_malloc(tmp->next = (t_lines*)malloc(sizeof(t_lines)));
			tmp = tmp->next;
			j--;
		}
		i--;
	}
	tmp->next = NULL;
}
