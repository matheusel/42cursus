/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:57:04 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/02 13:50:13 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Splits a string into groups based on quotes, spaces, variables,
 * and tokens.
 * @param str The string to be split.
 * @return A linked list of split nodes.
 *
 * This function splits the given string into groups based on quotes, spaces,
 * variables, and tokens. It returns a linked list of split nodes.
 */
t_split	*split_by_group(const char *str)
{
	size_t	i;
	t_split	*strs;
	t_split	*current;

	i = 0;
	strs = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			current = new_split_node(copy_quote(&str[i]));
		else if (ft_isspace(str[i]))
			current = new_split_node(copy_space(&str[i]));
		else if (str[i] == '$')
			current = new_split_node(copy_var(&str[i]));
		else
			current = new_split_node(copy_token(&str[i]));
		append(&strs, current);
		i += ft_strlen(current->str);
	}
	return (strs);
}

/**
 * @brief Copies a quote character from the string.
 * @param str The string containing the quote.
 * @return A new string containing the quote character.
 *
 * This function copies a single quote character from the given string and
 * returns it as a new string.
 */
char	*copy_quote(const char *str)
{
	return (ft_strndup(str, 1));
}

/**
 * @brief Copies consecutive space characters from the string.
 * @param str The string containing the spaces.
 * @return A new string containing the space characters.
 *
 * This function copies consecutive space characters from the given string and
 * returns them as a new string.
 */
char	*copy_space(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (ft_strndup(str, i));
}

/**
 * @brief Copies a token from the string.
 * @param str The string containing the token.
 * @return A new string containing the token.
 *
 * This function copies a token from the given string until it encounters a
 * whitespace, quote, or dollar sign character. It returns the token as a
 * new string.
 */
char	*copy_token(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '"'
		&& str[i] != '$')
		i++;
	return (ft_strndup(str, i));
}

/**
 * @brief Copies a variable from the string.
 * @param str The string containing the variable.
 * @return A new string containing the variable.
 *
 * This function copies a variable from the given string. If the variable starts
 * with a digit, it copies only the dollar sign. Otherwise, it copies the
 * variable name until it encounters a whitespace or non-alphanumeric character.
 */
char	*copy_var(const char *str)
{
	size_t	i;

	i = 1;
	if (ft_isdigit(str[i]))
		return (ft_strndup(str, 1));
	else if (str[i] == '?')
		return (ft_strndup(str, 2));
	while (str[i] && !ft_isspace(str[i]) && (ft_isalnum(str[i])
			|| str[i] == '_'))
		i++;
	return (ft_strndup(str, i));
}
