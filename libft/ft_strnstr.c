/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:29:29 by mc-m-el-          #+#    #+#             */
/*   Updated: 2023/11/12 20:15:06 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i])
	{
		x = 0;
		while (big[i + x] == little[x] && big[i + x] && (i + x) < len)
			x++;
		if (little[x] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (0);
}
