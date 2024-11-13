/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:14:35 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 11:39:58 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**allocate_paths(int count)
{
	char	**paths;

	paths = (char **)malloc((count + 1) * sizeof(char *));
	if (!paths)
		return (NULL);
	return (paths);
}

char	*allocate_and_copy_path(const char *start, int length)
{
	char	*path;

	path = (char *)malloc((length + 1) * sizeof(char));
	if (!path)
		return (NULL);
	ft_strncpy(path, start, length);
	path[length] = '\0';
	return (path);
}

void	free_paths_on_error(char **paths, int i)
{
	while (--i >= 0)
		free(paths[i]);
	free(paths);
}

void	free_env_on_error(t_env_list **env_list, char **key, char **value)
{
	free(*key);
	*key = NULL;
	free(*value);
	*value = NULL;
	free_env_list(*env_list);
	*env_list = NULL;
}
