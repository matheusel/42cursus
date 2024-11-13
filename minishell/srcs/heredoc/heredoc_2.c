/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:43:29 by mc-m-el-          #+#    #+#             */
/*   Updated: 2024/11/12 19:42:57 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Splits a given line into tokens that need to be expanded.
 *
 * @param line The input line to be split and expanded.
 * @return A pointer to the head of the linked list of split tokens.
 *
 * This function processes the input line character by character and splits it
 * into tokens based on quotes, spaces, variables, and other characters. Each
 * token is stored in a linked list node, and the function returns the head of
 * this linked list.
 */
t_split	*split_to_expand(const char *line)
{
	size_t	i;
	t_split	*strs;
	t_split	*current;

	i = 0;
	strs = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			current = new_split_node(copy_quote(&line[i]));
		else if (isspace(line[i]))
			current = new_split_node(copy_space(&line[i]));
		else if (line[i] == '$')
			current = new_split_node(copy_var(&line[i]));
		else
			current = new_split_node(copy_token(&line[i]));
		append(&strs, current);
		i += strlen(current->str);
	}
	return (strs);
}

/**
 * @brief Expands environment variables in a linked list of strings.
 *
 * @param list A pointer to the head of the linked list of strings (t_split).
 * @param env_list A pointer to the environment variables list (t_env_list).
 * @return A single string resulting from the concatenation of the expanded
 * strings.
 *
 * This function iterates through a linked list of strings, checking if each
 * string starts with a dollar sign ('$'). If it does, it attempts to expand
 * the string using the provided environment variables list. The original
 * string is replaced with the expanded value or an empty string if the
 * variable is not found. The function then concatenates all the strings in
 * the list into a single string and returns it.
 */
char	*expand_split_list_here(t_split **list, t_env_list *env_list)
{
	char	*expanded;
	t_split	*tmp;

	tmp = *list;
	while (tmp)
	{
		expanded = NULL;
		if (tmp->str[0] == '$' && tmp->str[1])
		{
			expanded = getenv_ll(env_list, tmp->str + 1);
			free(tmp->str);
			if (expanded)
				tmp->str = ft_strdup(expanded);
			else
				tmp->str = ft_strdup("");
			if (!tmp->str)
				exit(1);
		}
		tmp = tmp->next;
	}
	return (t_split_to_str(list));
}
