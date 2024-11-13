/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_validation_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:30:55 by dherszen          #+#    #+#             */
/*   Updated: 2024/10/17 15:13:27 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a syntax error message to the standard error output.
 * @param type The type of syntax error to print. This should be one of the
 * predefined constants (e.g., PIPE, REDIR_IN, REDIR_OUT, REDIR_APPEND, HEREDOC).
 *
 * This function takes an error type and prints a corresponding syntax error
 * message to the standard error output (STDERR_FILENO). The error types
 * correspond to different shell syntax errors such as unexpected tokens for
 * pipes, redirections, and heredocs.
 *
 *
 * @return Always returns true.
 */
int	print_syntax_error(int type)
{
	if (type == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
			STDERR_FILENO);
	else if (type == REDIR_IN)
		ft_putstr_fd("minishell: syntax error near unexpected token '<'\n",
			STDERR_FILENO);
	else if (type == REDIR_OUT)
		ft_putstr_fd("minishell: syntax error near unexpected token '>'\n",
			STDERR_FILENO);
	else if (type == REDIR_APPEND)
		ft_putstr_fd("minishell: syntax error near unexpected token '>>'\n",
			STDERR_FILENO);
	else if (type == HEREDOC)
		ft_putstr_fd("minishell: syntax error near unexpected token '<<'\n",
			STDERR_FILENO);
	else
		ft_putstr_fd("minishell: syntax error near input\n",
			STDERR_FILENO);
	return (true);
}

/**
 * @brief Checks if the pipe character in the input string is invalid.
 * @param input The input string to be checked.
 * @param i A pointer to the current index in the input string.
 *
 * This function examines the input string starting from the position
 * indicated by the pointer `i` to determine if the pipe character is
 * followed by another pipe or an end of string, which would make it invalid.
 * If an invalid pipe is detected, a syntax error is printed.
 *
 * @return true if the pipe is invalid, false otherwise.
 */
static int	is_invalid_pipe(const char *input, int *i)
{
	int	j;

	j = *i + 1;
	while (input[j] && ft_isspace(input[j]))
		j++;
	if (is_pipe(input[j]) || !input[j])
	{
		print_syntax_error(PIPE);
		return (true);
	}
	return (false);
}

/**
 * @brief Checks for syntax errors related to pipes in the input string.
 * @param input The input string to be checked for pipe-related syntax errors.
 *
 * This function scans the input string to detect any syntax errors related
 * to pipes. It ensures that pipes are not placed at the beginning of the
 * input and that they are not used incorrectly within the input, considering
 * the state of single and double quotes.
 *
 * @return Returns true if a syntax error is found, otherwise false.
 */
int	check_pipes_errors(const char *input)
{
	int	i;
	int	single_quote_state;
	int	double_quote_state;

	single_quote_state = 0;
	double_quote_state = 0;
	i = -1;
	while (input[++i] && ft_isspace(input[i]))
		continue ;
	if (is_pipe(input[i]))
	{
		print_syntax_error(PIPE);
		return (true);
	}
	while (input[i])
	{
		update_quote_state(input[i], &single_quote_state, &double_quote_state);
		if (is_pipe(input[i]) && !single_quote_state && !double_quote_state)
			if (is_invalid_pipe(input, &i))
				return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Checks if the given string starts with a quote and has a matching
 * closing quote.
 * @param str The input string to check.
 *
 * This function verifies if the input string starts with a single quote (')
 * or double quote (") and if there is a corresponding closing quote later in
 * the string.
 *
 * @return true if the string starts with a quote and has a matching closing
 * quote, false otherwise.
 */
int	is_closed_quote(const char *str)
{
	if (!str || !str[0])
		return (false);
	if ((*str == '\'' || *str == '"') && ft_strchr(str + 1, *str))
		return (true);
	return (false);
}
