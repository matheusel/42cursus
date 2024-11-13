/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_validation_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:59:19 by dherszen          #+#    #+#             */
/*   Updated: 2024/10/17 15:17:17 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a character is a redirection operator.
 * @param c The character to check.
 *
 * This function determines if the given character is a redirection operator,
 * specifically '<' or '>'.
 *
 * @return int Returns 1 if the character is a redirection operator, 0 otherwise.
 */
int	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

/**
 * @brief Checks the sequence of operators in a given string.
 * @param str The input string to be checked.
 *
 * This function validates the sequence of operators in the input string `str`.
 * It skips any leading whitespace characters and then checks if the string
 * starts with an operator. If it does, it continues to the next non-whitespace
 * character and checks if it is also an operator. The function returns true if
 * the sequence of operators is valid according to the following rules:
 * - A redirection operator followed by a pipe operator is valid.
 * - A pipe operator followed by a redirection operator is valid.
 * - Two consecutive redirection operators are valid.
 *
 * @return true if the sequence of operators is valid, false otherwise.
 */
int	check_operator_sequence(const char *str)
{
	int			op_size;
	int			next_op_size;
	char		*next;

	while (*str && ft_isspace(*str))
		str++;
	op_size = is_operator(str);
	next = (char *)str + op_size;
	if (!op_size)
		return (false);
	while (*next && ft_isspace(*next))
		next++;
	next_op_size = is_operator(next);
	if (!next_op_size)
		return (false);
	if ((is_redirection(*str) && *next == '|')
		|| (*str == '|' && is_redirection(*next))
		|| (is_redirection(*str) && is_redirection(*next)))
		return (true);
	return (false);
}

/**
 * @brief Handles the state of quotes in a given input string.
 * @param input The input string to be processed.
 * @param i Pointer to the current index in the input string.
 * @param in_quotes Pointer to the flag indicating if currently inside quotes.
 * @param closing_quote Pointer to the character representing the closing quote.
 *
 * This function checks the current character in the input string to determine
 * if it is a quote and updates the state accordingly. If not currently inside
 * quotes and an opening quote is found, it sets the closing quote and updates
 * the state to indicate being inside quotes. If inside quotes and the closing
 * quote is found, it resets the state to indicate being outside quotes.
 *
 * @return: true if the state was successfully updated, false otherwise.
 */
int	handle_quotes(const char *input, int *i, int *in_quotes,
char *closing_quote)
{
	if (!*in_quotes && (is_simple_quote(input[*i])
			|| is_double_quote(input[*i]))
		&& !is_closed_quote(&input[*i]))
		return (false);
	else if (!*in_quotes && is_closed_quote(&input[*i]))
	{
		*closing_quote = input[*i];
		*in_quotes = 1;
	}
	else if (*in_quotes && input[*i] == *closing_quote)
	{
		*in_quotes = 0;
		*closing_quote = '\0';
	}
	return (true);
}
