/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:18:22 by dherszen          #+#    #+#             */
/*   Updated: 2024/10/22 18:09:07 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int		i;
	size_t	dest_len;

	i = -1;
	dest_len = ft_strlen(dest);
	while (src[++i])
		dest[dest_len + (size_t)i] = src[i];
	dest[dest_len + (size_t)i] = '\0';
	return (dest);
}
