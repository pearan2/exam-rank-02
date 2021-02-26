/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:20:17 by honlee            #+#    #+#             */
/*   Updated: 2021/02/26 15:37:22 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int			ft_printf(const char *format, ...);

int			main()
{
//	ft_printf("test%d\n",123);
//	ft_printf("%15.15s\n", "this is test");
//	printf("%15.15s\n", "this is test");

	ft_printf("%s\n", NULL);
	printf("%s\n",NULL);

}
