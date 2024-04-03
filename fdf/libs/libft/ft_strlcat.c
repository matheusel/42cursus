/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:39:37 by mc-m-el-          #+#    #+#             */
/*   Updated: 2023/11/14 15:58:00 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;
	size_t	srcsize;
	size_t	i;

	i = 0;
	srcsize = ft_strlen(src);
	if (!dst && size == 0)
		return (srcsize);
	dstsize = ft_strlen(dst);
	if (size <= dstsize)
		return (size + srcsize);
	while (src[i] && dstsize + 1 < size)
	{
		dst[dstsize] = src[i];
		dstsize++;
		i++;
	}
	dst[dstsize] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
