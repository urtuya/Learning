/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:00:25 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/18 21:19:56 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		find_index(char c)
{
	char	*arr;
	int		i;

	arr = "0123456789abcdef";
	i = 0;
	if (c <= 'F' && c >= 'A')
		c += 0x20;
	while (i < 16)
	{
		if (arr[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		hex_atoi(char *str)
{
	int		i;
	int		j;
	int		ret;

	if (str[0] != '0' || str[1] != 'x')
		ft_error("Color must be like this: '0xFFFFFF' or '0xffffff'");
	i = 2;
	ret = 0;
	while (i < 8)
	{
		j = find_index(str[i]);
		if (j < 0)
			ft_error("Color must be like this: '0xFFFFFF' or '0xffffff'");
		ret = ret * 16 + j;
		i++;
	}
	return (ret);
}
