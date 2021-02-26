/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:56:10 by honlee            #+#    #+#             */
/*   Updated: 2021/02/26 13:02:07 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int		main()
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = 0;
	}
	printf("%s", line);
	free(line);
	line = 0;
}
