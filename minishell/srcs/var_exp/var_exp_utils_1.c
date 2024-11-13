/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:57:16 by dherszen          #+#    #+#             */
/*   Updated: 2024/10/29 12:36:14 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes surrounding quotes from a string.
 * @param str The string from which to remove quotes.
 * @return The string without surrounding quotes.
 *
 * This function removes the surrounding single or double quotes from the given
 * string if they exist. It returns the modified string.
 */
char	*remove_surrounding_quotes(char *str)
{
	char	*result;
	size_t	len;

	len = 0;
	if ((*str != '\'' && *str != '"') || !str[0] || !str[1])
		return (str);
	while (str[len])
		len++;
	if (str[len - 1] != *str)
		return (str);
	result = ft_strndup(str + 1, len - 2);
	free(str);
	return (result);
}

static char	*copy_quote_group(const char *str);
static char	*copy_non_quote_group(const char *str);

/**
 * @brief Splits a string by quote groups.
 * @param str The string to be split.
 * @return A linked list of split nodes.
 *
 * This function splits the given string into groups based on quotes. It returns
 * a linked list of split nodes.
 */
t_split	*split_by_quote_group(const char *str)
{
	t_split	*strs;
	t_split	*current;
	size_t	i;

	i = 0;
	strs = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			current = new_split_node(copy_quote_group(&str[i]));
		else
			current = new_split_node(copy_non_quote_group(&str[i]));
		append(&strs, current);
		i += ft_strlen(current->str);
	}
	return (strs);
}

/**
 * @brief Copies a non-quote group from the string.
 * @param str The string containing the non-quote group.
 * @return A new string containing the non-quote group.
 *
 * This function copies a non-quote group from the given string and returns
 * it as a new string.
 */
static char	*copy_non_quote_group(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\'' && str[len] != '"')
		len++;
	return (ft_strndup(str, len));
}

/**
 * @brief Copies a quote group from the string.
 * @param str The string containing the quote group.
 * @return A new string containing the quote group.
 *
 * This function copies a quote group from the given string and returns it as a
 * new string.
 */
static char	*copy_quote_group(const char *str)
{
	size_t	len;

	len = 1;
	while (str[len] && str[len] != *str)
		len++;
	return (ft_strndup(str, len + 1));
}
