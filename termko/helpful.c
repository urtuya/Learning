/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:49:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/20 15:38:52 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

int		loop_hook(t_fdf *fdf)
{
	static double i = 0.5;

	if (fdf->rotate)
	{
		if (fdf->project)
		{
			recreate_picture(fdf, 1);
			fdf->rotate = 1;
			rotate_x(fdf, 30);
			rotate_z(fdf, i);
			i += 0.5;
			if (i >= 360)
				i = 0;
			normalize_y(fdf);
		}
		else
			rotate_z(fdf, 0.5);
		recreate_picture(fdf, 0);
	}
	return (0);
}

int		ft_count(char **line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}
