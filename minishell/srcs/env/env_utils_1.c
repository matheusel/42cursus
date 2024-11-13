/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:36:56 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/01 17:00:00 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_array_size(char **envp)
{
	size_t	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

char	*get_envp_key(char *env)
{
	char	*key;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		return (NULL);
	key = ft_strndup(env, ft_strchr(env, '=') - env);
	return (key);
}

char	*get_envp_value(char *env)
{
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		return (NULL);
	value = ft_strdup(ft_strchr(env, '=') + 1);
	return (value);
}

t_env_node	*create_node(const char *key, const char *value)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node) * 1);
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_env_node(t_env_list *env_list, t_env_node *new)
{
	if (!new && !env_list)
		return ;
	if (!env_list->head)
	{
		env_list->head = new;
		env_list->tail = new;
	}
	else
	{
		env_list->tail->next = new;
		new->prev = env_list->tail;
		env_list->tail = new;
	}
}
