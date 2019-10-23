/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:57:51 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/18 21:12:26 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		mouse_press(int button, int x, int y, t_fdf *fdf)
{
	int	rotate;

	rotate = fdf->rotate;
	fdf->rotate = 0;
	if (button == 1)
	{
		fdf->mouse = 1;
		fdf->clickx = x;
		fdf->clicky = y;
	}
	if (button == 2)
	{
		fdf->mouse = 2;
		fdf->clickx = x;
		fdf->clicky = y;
	}
	if (button == 4 || button == 5)
		fdf->rotate = rotate;
	if (button == 4)
		scroll_up(fdf);
	if (button == 5)
		scroll_down(fdf);
	return (0);
}

int		mouse_release(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1 || button == 2)
		fdf->mouse = 0;
	(void)x;
	(void)y;
	(void)fdf;
	return (0);
}

void	mouse_helper(int x, int y, t_fdf *fdf)
{
	if (fdf->project)
	{
		recreate_picture(fdf, 1);
		if (fdf->shift)
			rotate_x(fdf, y);
		else
		{
			rotate_x(fdf, 30);
			rotate_z(fdf, x);
		}
		normalize_y(fdf);
	}
	else
		rotate_z(fdf, x - fdf->clickx);
	recreate_picture(fdf, 0);
}

void	rotate_x(t_fdf *fdf, double angle)
{
	double	**mat;

	mat = create_rot_x(angle * M_PI / 180);
	mult_matrix(fdf, mat, 1);
	free_matrix(mat);
}

void	rotate_z(t_fdf *fdf, double angle)
{
	double	**mat;

	mat = create_rot_z(angle * M_PI / 180);
	mult_matrix(fdf, mat, 1);
	free_matrix(mat);
}
