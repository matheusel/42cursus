/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:03:57 by mc-m-el-          #+#    #+#             */
/*   Updated: 2023/11/12 22:34:33 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (0);
	if (dst < src)
		return (ft_memcpy(dst, src, n));
	while (n--)
		((char *)dst)[n] = ((char *)src)[n];
	return (dst);
}
