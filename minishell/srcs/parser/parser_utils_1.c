/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/17 15:35:41 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_simple_quote(char c)
{
	return (c == '\'');
}

int	is_double_quote(char c)
{
	return (c == '\"');
}

int	is_pipe(char c)
{
	return (c == '|');
}

/**
 * @brief Updates the state of single and double quotes.
 *
 * @param c The current character being processed.
 * @param single_quote_state Pointer to the state of single quotes.
 * @param double_quote_state Pointer to the state of double quotes.
 *
 * This function toggles the state of single or double quotes based on the
 * current character. If the character is a single quote and double quotes
 * are not active, it toggles the single quote state. Similarly, if the
 * character is a double quote and single quotes are not active, it toggles
 * the double quote state.
 */
void	update_quote_state(char c, int *single_quote_state,
int *double_quote_state)
{
	if (c == '\'' && *double_quote_state == 0)
		*single_quote_state = !*single_quote_state;
	else if (c == '"' && *single_quote_state == 0)
		*double_quote_state = !*double_quote_state;
}

/**
 * @brief Counts the number of pipe characters in the input string
 *               while ignoring pipes inside single or double quotes.
 * @param input The input string to be parsed.
 *
 * This function iterates through the input string and counts the number
 * of pipe ('|') characters that are not enclosed within single ('\'') or
 * double ('"') quotes. It maintains state variables to track whether the
 * current character is within single or double quotes and only increments
 * the pipe count when it encounters a pipe character outside of these quotes.
 *
 * @return: The number of pipe characters found outside of quotes.
 */
int	count_pipes(const char *input)
{
	int	i;
	int	single_quote_state;
	int	double_quote_state;
	int	pipe_count;

	i = 0;
	single_quote_state = 0;
	double_quote_state = 0;
	pipe_count = 0;
	while (input[i])
	{
		if (is_simple_quote(input[i]) && double_quote_state == 0)
			single_quote_state = !single_quote_state;
		else if (is_double_quote(input[i]) && single_quote_state == 0)
			double_quote_state = !double_quote_state;
		else if (is_pipe(input[i]) && single_quote_state == 0
			&& double_quote_state == 0)
			pipe_count++;
		i++;
	}
	return (pipe_count);
}
