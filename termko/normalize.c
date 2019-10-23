/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:01:56 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/18 13:57:32 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	normalize_arr(t_points *str)
{
	int i;
	int j;

	i = 0;
	while (i < str->length)
	{
		j = 0;
		while (j < str->width)
		{
			(str->arrx)[i][j] -= (double)(str->width) / 2;
			(str->arry)[i][j] -= (double)(str->length) / 2;
			if (fabs(str->max_height) > fabs(str->min_height)\
					&& str->max_height != 0)
				(str->arrz)[i][j] /= fabs(str->max_height) / 5;
			else if (str->min_height != 0)
				(str->arrz)[i][j] /= fabs(str->min_height) / 5;
			j++;
		}
		i++;
	}
}
