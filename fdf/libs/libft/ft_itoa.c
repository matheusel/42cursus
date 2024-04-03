/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:22:00 by mc-m-el           #+#    #+#             */
/*   Updated: 2023/11/20 16:29:40 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(long int n)
{
	int	v;

	v = 0;
	if (n < 0)
	{
		n *= -1;
		v++;
	}
	while (n > 0)
	{
		n /= 10;
		v++;
	}
	return (v);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	x;

	x = (long int)n;
	if (x == 0)
		return (ft_strdup("0"));
	len = ft_length(x);
	str = (char *)malloc(sizeof(char) * len +1);
	if ((!str))
		return (0);
	if (x < 0)
	{
		str[0] = '-';
		x *= -1;
	}
	str[len] = '\0';
	while (x > 0)
	{
		str[--len] = x % 10 + '0';
		x = x / 10;
	}
	return (str);
}
