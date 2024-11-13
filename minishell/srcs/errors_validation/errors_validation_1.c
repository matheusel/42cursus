/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_validation_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:45 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 18:27:28 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check for errors in quotes, pipes, and operators in the input.
 * @param input The input string to be validated.
 *
 * This function validates the input string for common syntax errors such as
 * mismatched quotes, incorrect pipe usage, and invalid operators. It calls
 * helper functions to perform these checks and returns a boolean indicating
 * whether any errors were found.
 *
 * @return true if any errors are found, false otherwise.
 */
int	check_input_errors(const char *input)
{
	if (check_quotes_errors(input))
	{
		g_status = 2;
		return (true);
	}
	if (check_pipes_errors(input))
	{
		g_status = 2;
		return (true);
	}
	if (!is_valid_input(input))
	{
		g_status = 2;
		return (true);
	}
	return (false);
}

/**
 * @brief Checks if the given string is an operator.
 * @param str The string to be checked.
 *
 * This function checks if the provided string matches any of the predefined
 * operators: "<<", ">>", "<", ">", or "|". If a match is found, the function
 * returns the length of the operator.
 *
 * @return: The length of the operator if a match is found, otherwise false.
 */
int	is_operator(const char *str)
{
	static const char	*operators[] = {"<<", ">>", "<", ">", "|", NULL};
	int					index;
	int					size;

	index = 0;
	if (!str || !*str)
		return (false);
	while (operators[index])
	{
		size = (int)strlen(operators[index]);
		if (ft_strncmp(operators[index], str, size) == 0)
			return (size);
		index++;
	}
	return (false);
}

/**
 * @brief Helper function to check for invalid operator usage in a shell
 * command string.
 * @param str The input string to be checked for invalid operator usage.
 *
 * This function checks if the given string contains invalid operator usage,
 * such as:
 * - Consecutive redirection operators (e.g., '<<', '>>') at the end of the
 *   string.
 * - A pipe operator ('|') at the end of the string.
 * - Any operator followed by an unexpected token or end of the string.
 *
 * @return int Returns true (non-zero) if an invalid operator usage is detected
 *         and prints the corresponding syntax error message. Returns false
 *         (zero) otherwise.
 */
static int	invalid_operator(const char *str)
{
	int			operator_size;
	int			next_operator_size;
	const char	*next_char;

	operator_size = is_operator(str);
	if (!operator_size)
		return (false);
	next_char = str + operator_size;
	while (*next_char && ft_isspace(*next_char))
		next_char++;
	next_operator_size = is_operator(next_char);
	if (next_operator_size)
	{
		if ((is_redirection(*str) && is_redirection(*next_char)))
			return (print_syntax_error(REDIR_IN));
	}
	if (!*next_char)
	{
		if (*str == '|')
			return (print_syntax_error(PIPE));
		ft_putstr_fd("minishell: syntax error near unexpected token \
'newline'\n", STDERR_FILENO);
		return (true);
	}
	return (false);
}

/**
 * @brief Check the overall validity of the input (quotes, pipes,
 * operators)
 * @param input The input string to be validated
 *
 * This function validates the input string by ensuring that quotes are properly
 * closed and that there are no invalid operators when not inside quotes. It
 * iterates
 * through each character of the input string, handling quotes and checking
 * for invalid operators. If the input is valid, it returns true; otherwise,
 * it returns false.
 *
 * @return: true if the input is valid, false otherwise
 */
int	is_valid_input(const char *input)
{
	char	closing_quote;
	int		in_quotes;
	int		i;

	i = -1;
	in_quotes = 0;
	closing_quote = '\0';
	while (input[++i])
	{
		if (!handle_quotes(input, &i, &in_quotes, &closing_quote))
			return (false);
		if (!in_quotes && invalid_operator(&input[i]))
			return (false);
	}
	return (true);
}

/**
 * @brief Checks for unmatched quotes in the input string.
 * @param input The input string to check for unmatched quotes.
 *
 * This function iterates through the input string and updates the state
 * of singleand double quotes. If there are any unmatched quotes by the end
 * of the string, it prints an appropriate error message to the standard
 * error output.
 *
 * @return Returns true (non-zero) if there are unmatched quotes, false (zero)
 *         otherwise.
 */
int	check_quotes_errors(const char *input)
{
	int		single_quote_state;
	int		double_quote_state;
	int		i;

	single_quote_state = 0;
	double_quote_state = 0;
	i = -1;
	while (input[++i])
		update_quote_state(input[i], &single_quote_state, &double_quote_state);
	if (single_quote_state || double_quote_state)
	{
		if (single_quote_state)
			ft_putstr_fd("minishell: syntax error: unexpected EOF while \
looking for matching '\n", STDERR_FILENO);
		else if (double_quote_state)
			ft_putstr_fd("minishell: syntax error: unexpected EOF while \
looking for matching \"\n", STDERR_FILENO);
		return (true);
	}
	return (false);
}
