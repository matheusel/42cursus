/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:55:32 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 11:34:38 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_export_error(char **key, char **value)
{
	free_key_value(key, value);
	return (EXIT_FAILURE);
}

const char	**split_path_value(const char *value)
{
	int		count;
	char	**paths;

	count = count_paths(value);
	paths = fill_paths(value, count);
	return ((const char **)paths);
}

int	count_paths(const char *value)
{
	int			count;
	const char	*p = value;

	count = 1;
	while (*p)
	{
		if (*p == ':')
			count++;
		p++;
	}
	return (count);
}

char	**fill_paths(const char *value, int count)
{
	char	**paths;
	int		result;

	paths = allocate_paths(count);
	if (!paths)
		return (NULL);
	result = fill_paths_loop(value, paths);
	if (result != -1)
	{
		free_paths_on_error(paths, result);
		return (NULL);
	}
	paths[count] = NULL;
	return (paths);
}

int	fill_paths_loop(const char *value, char **paths)
{
	const char	*start = value;
	int			i;
	int			length;

	i = 0;
	while (*value)
	{
		if (*value == ':')
		{
			length = value - start;
			paths[i] = allocate_and_copy_path(start, length);
			if (!paths[i])
				return (i);
			i++;
			start = value + 1;
		}
		value++;
	}
	paths[i] = ft_strdup(start);
	if (!paths[i])
		return (i);
	return (-1);
}
