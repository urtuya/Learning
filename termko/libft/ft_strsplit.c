/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:04:42 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/19 14:10:16 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			ret++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (ret);
}

static char	**ft_null_count(void)
{
	char **str;

	if (!(str = (char**)malloc(sizeof(char*))))
		return (NULL);
	*str = NULL;
	return (str);
}

static char	**free_mem(char ***ret, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		if (*ret[j])
			free(*ret[i]);
		i++;
	}
	if (*ret)
		free(*ret);
	return (NULL);
}

static char	*malloc_word(const char *s, int i, char c)
{
	char	*ret;
	int		j;
	int		k;

	j = i;
	k = 0;
	while (s[j] && s[j] != c)
		j++;
	if (!(ret = (char*)malloc(sizeof(char) * (j - i + 2))))
		return (NULL);
	j = i;
	while (s[j] && s[j] != c)
	{
		ret[k] = s[j];
		j++;
		k++;
	}
	ret[k] = '\0';
	return (ret);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!(count = count_words(s, c)))
		return (ft_null_count());
	if (!(ret = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && !(ret[j] = malloc_word(s, i, c)))
			return (free_mem(&ret, count));
		j++;
		while (s[i] && s[i] != c)
			i++;
	}
	ret[count] = NULL;
	return (ret);
}
