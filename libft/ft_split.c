/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:46:10 by mc-m-el-          #+#    #+#             */
/*   Updated: 2023/11/20 22:23:25 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		x;
	int		len;
	int		start;

	str = (char **) malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!s || !str)
		return (0);
	start = -1;
	i = -1;
	x = 0;
	len = ft_strlen(s);
	while (++i <= len)
	{
		if (s[i] != c && start == -1)
			start = i;
		else if (start != -1 && (s[i] == c || i == len))
		{
			str[x++] = ft_substr(s, start, i - start);
			start = -1;
		}
	}
	str[x] = '\0';
	return (str);
}
