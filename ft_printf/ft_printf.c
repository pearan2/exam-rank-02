/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:59:05 by honlee            #+#    #+#             */
/*   Updated: 2021/02/26 15:52:29 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct	s_info
{
	char		format;
	int			width;
	int			precision;
	int			is_dot;
	int			is_error;
}				t_info;

int				g_ret;

void			ft_init_info(t_info *info)
{
	info->width = 0;
	info->precision = 0;
	info->format = 0;
	info->is_dot = 0;
	info->is_error = 0;
}

void			ft_putchar(char c)
{
	g_ret++;
	write(1, &c, 1);
}

int				ft_parse_w_p(const char *format, int *idx)
{
	int			ret = 0;
	while (format[*idx] >= '0' && format[*idx] <= '9')
	{
		ret = ret * 10 + (format[*idx] - '0');
		*idx = *idx + 1;
	}
	return (ret);
}

void			ft_parse(const char *format, int *idx, t_info *info)
{
	*idx = *idx + 1;
	if (format[*idx] >= '0' && format[*idx] <= '9')
		info->width = ft_parse_w_p(format, idx);
	if (format[*idx] == '.')
	{
		*idx = *idx + 1;
		info->is_dot = 1;
		info->precision = ft_parse_w_p(format, idx);
	}
	info->format = format[*idx];
}

int				ft_getlen_d(int value)
{
	int		ret = 0;
	while (value / 10 != 0)
	{
		value = value / 10;
		ret++;
	}
	ret++;
	if (value < 0)
		ret++;
	return (ret);
}

void			ft_putnbr(unsigned int value)
{
	if (value / 10 != 0)
		ft_putnbr(value / 10);
	ft_putchar((value % 10) + '0');
}

void			ft_printf_d(va_list *ap, t_info *info)
{
	int				value	= va_arg(*ap, int);
	unsigned int	v		= value < 0 ? value * (-1) : value;
	
	if (info->is_dot == 1 && info->precision == 0 && value == 0)
	{
		for(int i=0; i<info->width; i++)
			ft_putchar(' ');
		return ;
	}
	int				len		= ft_getlen_d(value);
	int				reallen = value < 0 ? len - 1 : len;
	info->precision -= reallen;
	info->width -= len;
	if (info->precision > 0)
		info->width -= info->precision;
	for(int i=0; i<info->width; i++)
		ft_putchar(' ');
	if (value < 0)
		ft_putchar('-');
	for(int i=0; i<info->precision; i++)
		ft_putchar('0');
	ft_putnbr(v);
}

int				ft_getlen_s(char *str)
{
	int			ret = 0;
	while (str[ret] != 0)
		ret++;
	return (ret);
}

void			ft_printf_s(va_list *ap, t_info *info)
{
	char		*value = va_arg(*ap, char *);
	if (!value)
		value = "(null)";
	int			len = ft_getlen_s(value);

	if (info->is_dot)
		len = info->precision < len ? info->precision : len;
	for(int i=0; i<info->width - len; i++)
		ft_putchar(' ');
	for(int i=0; i<len; i++)
		ft_putchar(value[i]);
}

int				ft_getlen_x(unsigned int value)
{
	int		ret = 0;
	while (value / 16 != 0)
	{
		value = value / 16;
		ret++;
	}
	ret++;
	return (ret);
}

void			ft_putx(unsigned int value)
{
	if (value / 16 != 0)
		ft_putx(value / 16);
	char *temp = "0123456789abcdef";
	ft_putchar(temp[value % 16]);
}

void			ft_printf_x(va_list *ap, t_info *info)
{
	unsigned int	value = va_arg(*ap, unsigned int);
	int				len = ft_getlen_x(value);

	if (info->is_dot == 1 && info->precision == 0 && value == 0)
	{
		for (int i=0; i<info->width; i++)
			ft_putchar(' ');
		return ;
	}
	info->precision -= len;
	info->width -= len;
	if (info->precision > 0)
		info->width -= info->precision;
	for (int i=0; i< info->width; i++)
		ft_putchar(' ');
	for (int i=0; i< info->precision; i++)
		ft_putchar('0');
	ft_putx(value);
}

void			ft_proc_mapper(va_list *ap, t_info *info)
{
	if (info->format == 'd')
		ft_printf_d(ap, info);
	else if (info->format == 's')
		ft_printf_s(ap, info);
	else if (info->format == 'x')
		ft_printf_x(ap, info);
}

int				ft_printf(const char *format, ...)
{
	g_ret = 0;
	va_list ap;
	t_info *info;

	if (!(info = malloc(sizeof(t_info))))
		return (-1);
	va_start(ap, format);	
	for (int i=0; format[i] != 0; i++)
	{
		if (format[i] == '%')
		{
			ft_init_info(info);
			ft_parse(format, &i, info);
			if (info->is_error)
			{
				free(info);
				return (-1);
			}
			ft_proc_mapper(&ap, info);
		}
		else
			ft_putchar(format[i]);
	}
	free(info);
	va_end(ap);
	return (g_ret);
}
