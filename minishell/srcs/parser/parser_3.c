/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:33:32 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 12:45:24 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Determines the type of redirection and its length from a command
 *        string.
 *
 * @param cmd The command string to analyze.
 * @param start The starting position in the command string to check for
 *              redirection.
 * @param redir_type Pointer to a variable where the determined redirection
 *                   type will be stored.
 * @param redir_len Pointer to a variable where the length of the redirection
 *                  operator will be stored.
 *
 * This function analyzes a command string starting at a given position to
 * identify the type of redirection (e.g., output redirection, input
 * redirection, append, or heredoc) and sets the corresponding redirection
 * type and length.
 */
static void	get_redirection_type(const char *cmd, int start,
t_token_type *redir_type, int *redir_len)
{
	*redir_len = 1;
	if (cmd[start] == '>' && cmd[start + 1] == '>')
	{
		*redir_type = REDIR_APPEND;
		*redir_len = 2;
	}
	else if (cmd[start] == '<' && cmd[start + 1] == '<')
	{
		*redir_type = HEREDOC;
		*redir_len = 2;
	}
	else if (cmd[start] == '>')
		*redir_type = REDIR_OUT;
	else
		*redir_type = REDIR_IN;
}

/**
 * @brief Determines the argument type based on the given redirection type.
 *
 * @param redir_type The type of redirection.
 *
 * This function takes a redirection type as input and returns the corresponding
 * argument type. The mapping is as follows:
 * - REDIR_APPEND -> APPEND_ARG
 * - HEREDOC -> HEREDOC_ARG
 * - REDIR_OUT -> OUT_ARG
 * - REDIR_IN -> IN_ARG
 * - Any other type -> CMD_ARG
 * @return The corresponding argument type.
 */
static t_token_type	get_argument_type(t_token_type redir_type)
{
	if (redir_type == REDIR_APPEND)
		return (APPEND_ARG);
	else if (redir_type == HEREDOC)
		return (HEREDOC_ARG);
	else if (redir_type == REDIR_OUT)
		return (OUT_ARG);
	else if (redir_type == REDIR_IN)
		return (IN_ARG);
	else
		return (CMD_ARG);
}

/**
 * @brief Handles the redirection argument in the token context.
 *
 * @param ctx Pointer to the token context.
 * @param current Pointer to the current position in the command string.
 * @param arg_type The type of the argument token to be added.
 *
 * This function processes the redirection argument in the given token context.
 * It updates the current position in the command string while considering
 * single and double quotes. If a valid argument is found, it adds a token
 * of the specified type to the context.
 */
void	handle_redirection_argument(t_token_context *ctx, int *current,
t_token_type arg_type)
{
	int		start;
	int		quote_single;
	int		quote_double;

	start = *current;
	quote_single = 0;
	quote_double = 0;
	while (ctx->cmd[*current])
	{
		update_quote_state(ctx->cmd[*current], &quote_single, &quote_double);
		if (!quote_single && !quote_double && (ft_isspace(ctx->cmd[*current])
				|| ctx->cmd[*current] == '>' || ctx->cmd[*current] == '<'))
			break ;
		(*current)++;
	}
	if (*current > start)
		add_token(ctx, start, *current, arg_type);
}

/**
 * @brief Processes a redirection in the command string.
 *
 * @param ctx Pointer to the token context structure.
 * @param current Pointer to the current position in the command string.
 *
 * This function identifies the type and length of a redirection operator
 * in the command string starting from the current position. It then adds
 * a token for the redirection to the token context and advances the current
 * position past the redirection operator. Any whitespace following the
 * redirection operator is skipped, and the function then processes the
 * argument for the redirection.
 */
void	handle_redirection(t_token_context *ctx, int *current)
{
	int				start;
	t_token_type	redir_type;
	int				redir_len;

	start = *current;
	get_redirection_type(ctx->cmd, start, &redir_type, &redir_len);
	add_token(ctx, start, start + redir_len, redir_type);
	*current += redir_len;
	while (ft_isspace(ctx->cmd[*current]))
		(*current)++;
	handle_redirection_argument(ctx, current, get_argument_type(redir_type));
}
