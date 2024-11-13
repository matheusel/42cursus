/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:58:19 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 11:41:11 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **envp, t_env_list *env_list)
{
	int				n;
	const size_t	env_size = get_array_size(envp);
	t_env_node		*new;
	char			*key;
	char			*value;

	n = -1;
	while (++n < (int)env_size)
	{
		key = get_envp_key(envp[n]);
		value = get_envp_value(envp[n]);
		if (!key)
			free(key);
		if (!value)
			free(value);
		new = create_node(key, value);
		if (!new)
			free_env_on_error(&env_list, &key, &value);
		if (!key || !value || !new)
			return ;
		add_env_node(env_list, new);
		free(key);
		free(value);
	}
}

void	free_env_list(t_env_list *env_list)
{
	t_env_node	*current;
	t_env_node	*next;

	if (!env_list || !env_list->head)
		return ;
	current = env_list->head;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	env_list->head = NULL;
	env_list->tail = NULL;
}

char	*getenv_ll(t_env_list *env_list, const char *key)
{
	t_env_node	*tmp;

	tmp = env_list->head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	set_env_value(t_env_list *env_list, const char *key, const char *value)
{
	t_env_node	*node;

	node = env_list->head;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
		{
			free(node->value);
			node->value = ft_strdup(value);
			if (!node->value)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		node = node->next;
	}
	node = create_node(key, value);
	if (!node)
		return (EXIT_FAILURE);
	add_env_node(env_list, node);
	return (EXIT_SUCCESS);
}

size_t	env_lst_size(t_env_list *env_lst)
{
	int			i;
	t_env_node	*tmp;

	tmp = env_lst->head;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
