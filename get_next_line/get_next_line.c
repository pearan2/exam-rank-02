/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:39:34 by honlee            #+#    #+#             */
/*   Updated: 2021/04/22 14:43:07 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		ft_strlen(const char *str)
{
	int ret = 0;
	while (str[ret] != 0)
		ret++;
	return (ret);
}

char	*ft_charappend(char *target, char value)
{
	int		idx = -1;
	char	*ret;

	ret = malloc(ft_strlen(target) + 2);
	while (target[++idx] != 0)
		ret[idx] = target[idx];
	ret[idx] = value;
	idx++;
	ret[idx] = 0;
	free(target);
	return (ret);
}

int		get_next_line(char **line)
{
	int		rb;
	char	buff;

	*line = malloc(1);
	(*line)[0] = 0;
	while ((rb = read(0, &buff, 1)) > 0)
	{
		if (buff == '\n')
			return (1);
		*line = ft_charappend(*line, buff);
	}
	if (rb == -1)
		return (-1);
	return (0);
}
