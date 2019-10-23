/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:04:44 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/22 19:34:44 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	scroll_up(t_fdf *fdf)
{
	fdf->points->coef *= 1.1;
	recreate_picture(fdf, 0);
}

void	scroll_down(t_fdf *fdf)
{
	fdf->points->coef *= 0.9;
	recreate_picture(fdf, 0);
}

int		key_hook_ext(int keycode, t_fdf *fdf, int i, int rotate)
{
	if (keycode == 257)
		fdf->shift = (fdf->shift ? 0 : 1);
	if (keycode == 15)
		fdf->rotate = (rotate ? 0 : 1);
	if (keycode == 8)
	{
		fdf->project = (fdf->project ? 0 : 1);
		i = 1;
	}
	return (i);
}

int		key_hook(int keycode, t_fdf *fdf)
{
	int	rotate;
	int	i;

	i = 0;
	rotate = fdf->rotate;
	fdf->rotate = 0;
	if (keycode == 53)
		exit(0);
	else if (keycode == 36)
		i = 1;
	else if (keycode == 4)
	{
		fdf->rotate = rotate;
		fdf->help = (fdf->help ? 0 : 1);
	}
	else
		i = key_hook_ext(keycode, fdf, i, rotate);
	recreate_picture(fdf, i);
	if (fdf->project)
	{
		normalize_y(fdf);
		rotate_x(fdf, 30);
		recreate_picture(fdf, 0);
	}
	return (0);
}

int		mouse_move(int x, int y, t_fdf *fdf)
{
	if (fdf->mouse == 2)
	{
		fdf->offx += x - fdf->clickx;
		fdf->offy += y - fdf->clicky;
		recreate_picture(fdf, 0);
	}
	if (fdf->mouse == 1)
		mouse_helper(x, y, fdf);
	fdf->clickx = x;
	fdf->clicky = y;
	return (0);
}
