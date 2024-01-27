/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:00 by mc-m-el           #+#    #+#             */
/*   Updated: 2024/01/16 17:12:48 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *buffer, char *line)
{
	char	*str;
	int		i;
	int		a;

	a = ft_strlen(buffer) + ft_strlen(line);
	str = (char *) malloc (sizeof(char) * (a + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			str[i] = buffer[i];
			i++;
		}
		free (buffer);
	}
	while (*line)
		str[i++] = *line++;
	str[i] = '\0';
	return (str);
}

char	*find_buffer(char *buffer, int n, int count)
{
	char	*str;
	int		i;
	int		j;

	if ((count < 1 && (!buffer)) || (count < 1 && !*buffer))
	{
		free (buffer);
		return (NULL);
	}
	i = ft_strlen(buffer);
	str = (char *) malloc (sizeof (char) * ((i - n) + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (n < i)
	{
		str[j] = buffer[n];
		j++;
		n++;
	}
	str[j] = '\0';
	free (buffer);
	return (str);
}

char	*hunter_str(int fd)
{
	char		*line;
	static char	*buffer;
	int			count;

	line = ((char *) malloc ((BUFFER_SIZE + 1) * sizeof(char)));
	if (!line)
		return (NULL);
	count = 1;
	while (count > 0 && confirm_n(buffer) < 1)
	{
		count = read(fd, line, BUFFER_SIZE);
		if (count == -1)
		{
			free (line);
			return (NULL);
		}
		line[count] = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	free (line);
	if (!buffer)
		return (NULL);
	line = find_n(buffer, ft_strlen_n(buffer));
	buffer = find_buffer (buffer, ft_strlen_n(buffer), count);
	return (line);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	return (hunter_str(fd));
}
