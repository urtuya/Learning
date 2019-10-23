/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:19:55 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/19 14:12:12 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*ft_newgnllst(const int fd, t_gnl **lst)
{
	t_gnl	*tmp;

	if (!(tmp = (t_gnl*)malloc(sizeof(t_gnl))))
		return (NULL);
	tmp->fd = fd;
	tmp->txt = NULL;
	tmp->next = NULL;
	if (lst)
		(*lst)->next = tmp;
	return (tmp);
}

static t_gnl	*ft_fdsearch(const int fd, t_gnl **lst)
{
	t_gnl	*tmp;

	if (!(*lst))
	{
		if (!((*lst) = ft_newgnllst(fd, NULL)))
			return (NULL);
		return (*lst);
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (tmp->next)
			tmp = tmp->next;
		else if (!(tmp->next = ft_newgnllst(fd, &tmp)))
			return (NULL);
		else
			break ;
	}
	return (tmp->next);
}

static char		*ft_newtxt(char *s1, char *s2)
{
	char	*tmp;

	if (!s1)
		return ((tmp = ft_strdup(s2)));
	if (!(tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	if (!(tmp = ft_strcat(tmp, s1)))
		return (NULL);
	if (!(tmp = ft_strcat(tmp, s2)))
		return (NULL);
	return (tmp);
}

static int		free_and_go(char **iter, char **line)
{
	char *tmp;
	char *end;

	if (!(end = ft_strchr(*iter, '\n')))
	{
		*line = ft_strdup(*iter);
		free(*iter);
		*iter = NULL;
		return (**line ? 1 : 0);
	}
	if (**iter == '\n')
	{
		if (!(*line = ft_strnew(1)))
			return (-1);
		**line = '\0';
	}
	else if (!(*line = ft_strsub(*iter, 0, end - *iter)))
		return (-1);
	if (!(tmp = ft_strdup(end + 1)))
		return (-1);
	free(*iter);
	*iter = tmp;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl		*lst;
	t_gnl				*iter;
	char				tmp[BUFF_SIZE + 1];
	char				*keks;
	int					i;

	if (!line || fd < 0 || read(fd, tmp, 0) < 0
			|| (!(iter = ft_fdsearch(fd, &lst))))
		return (-1);
	if (!(iter->txt))
		while ((i = read(fd, tmp, BUFF_SIZE)))
		{
			tmp[i] = '\0';
			keks = ft_newtxt(iter->txt, tmp);
			if (iter->txt)
				free(iter->txt);
			iter->txt = keks;
		}
	if (!iter->txt)
	{
		*line = ft_strdup("");
		return (0);
	}
	return (free_and_go(&(iter->txt), line));
}
