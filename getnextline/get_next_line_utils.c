/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:55:51 by mc-m-el           #+#    #+#             */
/*   Updated: 2024/01/13 14:55:54 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	confirm_n(char *buffer)
{
	int	i;

	if (!buffer)
		return (0);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '\n')
		return (1);
	while (str[i] && str[i] != '\n')
		i++;
	if (i > 0)
	{
		if (str[i] == '\n')
			return (i + 1);
		else
			return (i);
	}
	return (0);
}

char	*find_n(char *buffer, int n)
{
	char	*str;
	int		j;

	if (n < 1)
		return (NULL);
	str = (char *) malloc (sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < n)
	{
		str[j] = buffer[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
