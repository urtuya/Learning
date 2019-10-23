/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 21:53:24 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/19 16:23:30 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_tmp(char **tmp)
{
	while (*tmp)
		free(*tmp++);
}

void	free_lines(t_lines *lines)
{
	t_lines	*tmp;
	t_lines	*next;
	int		i;

	i = 0;
	tmp = lines;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->line);
		if (i)
			free(tmp);
		i = 1;
		tmp = next;
	}
}

void	check_malloc(void *addr)
{
	if (!addr)
		ft_error("Unexpected error with malloc.");
}

int		get_length(t_fdf *fdf, int fd)
{
	int		i;
	int		j;
	int		len;
	char	buff[BUFF_SIZE];

	fdf->points->length = 0;
	len = 0;
	while ((j = read(fd, buff, BUFF_SIZE)) > 0)
	{
		i = 0;
		while (i < j)
			if (buff[i++] == '\n')
				fdf->points->length++;
		len += i;
	}
	close(fd);
	return (len);
}

void	fill_str(char *file, char *str)
{
	char	buff[BUFF_SIZE];
	int		i;
	int		j;
	int		fd;
	int		len;

	if ((fd = open(file, 'r')) < 0)
		ft_error("Can't open file.");
	len = 0;
	while ((j = read(fd, buff, BUFF_SIZE)) > 0)
	{
		i = 0;
		while (i < j)
			str[len++] = buff[i++];
		str[len] = '\0';
	}
	close(fd);
}
