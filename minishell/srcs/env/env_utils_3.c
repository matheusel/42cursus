/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:05:25 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/06 11:59:43 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_create_env_var_array(const char *key, const char *sep,
				const char *value);

void	*free_my_envp(char **envp)
{
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (NULL);
}

char	**env_list_to_array(t_env_list *env_list)
{
	char				**envp;
	size_t				i;
	const t_env_node	*tmp = env_list->head;
	char				*key_value;

	envp = (char **)malloc(sizeof(char *) * (env_lst_size(env_list) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (tmp)
	{
		key_value = join_create_env_var_array(tmp->key, "=", tmp->value);
		if (!key_value)
			return (free_and_return(envp, NULL));
		envp[i++] = key_value;
		if (!key_value)
			return (free_my_envp(envp));
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	delete_env_node(t_env_list *env_list, const char *key)
{
	t_env_node	*tmp;

	tmp = env_list->head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				env_list->head = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			else
				env_list->tail = tmp->prev;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

void	free_key_value(char **key, char **value)
{
	if (key && *key)
	{
		free(*key);
		*key = NULL;
	}
	if (value && *value)
	{
		free(*value);
		*value = NULL;
	}
}

static char	*join_create_env_var_array(const char *key, const char *sep,
const char *value)
{
	const size_t	len1 = ft_strlen(key);
	const size_t	len2 = ft_strlen(sep);
	const size_t	len3 = ft_strlen(value);
	char *const		env_var = (char *)malloc(sizeof(char)
			* (len1 + len2 + len3 + 1));

	if (!env_var)
		return (NULL);
	ft_strlcpy(env_var, key, len1 + 1);
	ft_strlcat(env_var, sep, len1 + len2 + 1);
	ft_strlcat(env_var, value, len1 + len2 + len3 + 1);
	return (env_var);
}
