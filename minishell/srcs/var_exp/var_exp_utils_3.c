/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:08:12 by dherszen          #+#    #+#             */
/*   Updated: 2024/10/25 11:41:24 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends a node to the end of a linked list.
 * @param head A pointer to the head of the linked list.
 * @param node The node to be appended.
 *
 * This function appends the given node to the end of the linked list.
 */
void	append(t_split **head, t_split *node)
{
	t_split	*tmp;

	if (!node)
		printf("warning: trying to append NULL node to list\n");
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

/**
 * @brief Converts a linked list of split nodes to a string.
 * @param head A pointer to the head of the linked list.
 * @return The concatenated string.
 *
 * This function converts the linked list of split nodes to a single string.
 * It returns the concatenated string.
 */
char	*t_split_to_str(t_split **head)
{
	char	*str;
	char	*anchor;
	size_t	total_size;
	t_split	*tmp;

	total_size = 0;
	tmp = *head;
	while (tmp)
	{
		total_size += ft_strlen(tmp->str);
		tmp = tmp->next;
	}
	str = (char *)malloc(sizeof(*str) * (total_size + 1));
	if (!str)
		exit(EXIT_FAILURE);
	anchor = str;
	tmp = *head;
	while (tmp)
	{
		anchor = ft_stpcpy(anchor, tmp->str);
		tmp = tmp->next;
	}
	free_split_list(*head);
	*head = NULL;
	return (str);
}

/**
 * @brief Creates a new split node with the given content.
 * @param content The content for the new split node.
 * @return A pointer to the new split node.
 *
 * This function creates a new split node with the given content and returns
 * a pointer to the new node.
 */
t_split	*new_split_node(char *content)
{
	t_split *const	node = (t_split * const)malloc(sizeof(*node));

	if (!node)
	{
		perror(__func__);
		exit(1);
	}
	node->next = NULL;
	node->str = content;
	if (!content)
		printf("warning: creating node with NULL content\n");
	return (node);
}

/**
 * @brief Frees a linked list of split nodes.
 * @param list The linked list to be freed.
 *
 * This function frees all the nodes in the linked list of split nodes.
 */
void	free_split_list(t_split *list)
{
	t_split	*tmp;

	while (list)
	{
		tmp = list;
		list = tmp->next;
		free(tmp->str);
		free(tmp);
	}
}
