/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:25:24 by mc-m-el-          #+#    #+#             */
/*   Updated: 2023/11/10 23:25:48 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	tsize;

	tsize = nmemb * size;
	ptr = malloc(tsize);
	if (!ptr)
		return (0);
	ft_bzero(ptr, tsize);
	return (ptr);
}
