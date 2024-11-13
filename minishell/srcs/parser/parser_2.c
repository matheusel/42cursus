/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:15:20 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 11:49:26 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Tokenizes the command segments based on the number of pipes.
 *
 * @param segments An array of command segments to be tokenized.
 * @param pipe_count The number of pipes, which determines the number of
 *        segments.
 *
 * This function iterates through the provided command segments and tokenizes
 * each command if it is not NULL. The tokenization process involves breaking
 * down the command into tokens and storing them in the segment's token list.
 */
void	tokenize_segments(t_cmd **segments, int pipe_count)
{
	int				i;
	t_token			*last_token;

	i = -1;
	while (++i <= pipe_count)
	{
		if (segments[i] != NULL && segments[i]->cmd != NULL)
		{
			last_token = NULL;
			tokenize_command(segments[i]->cmd, &segments[i]->tokens_list,
				&last_token);
		}
	}
}

/**
 * @brief Processes a segment of the command string to identify tokens.
 * @param ctx Pointer to the token context containing the command string.
 * @param current Pointer to the current position in the command string.
 * @param start Pointer to the start position of the current token.
 * @param is_first_token Pointer to a flag indicating if the current token
 * is the first token.
 *
 * This function scans the command string from the current position to identify
 * and handle tokens. It updates the quote states and breaks on encountering
 * special characters like '>', '<', or whitespace when not inside quotes.
 * If a token is identified, it is added to the token context.
 */
static void	handle_token(t_token_context *ctx, int *current, int *start,
int *is_first_token)
{
	int				single_quote_state;
	int				double_quote_state;
	t_token_type	type;

	single_quote_state = 0;
	double_quote_state = 0;
	while (ctx->cmd[*current])
	{
		update_quote_state(ctx->cmd[*current], &single_quote_state,
			&double_quote_state);
		if ((!single_quote_state && !double_quote_state)
			&& ((ctx->cmd[*current] == '>' || ctx->cmd[*current] == '<')
				|| ft_isspace(ctx->cmd[*current])))
			break ;
		(*current)++;
	}
	if (*current > *start)
	{
		if (*is_first_token)
			type = CMD;
		else
			type = CMD_ARG;
		add_token(ctx, *start, *current, type);
		*is_first_token = 0;
	}
}

/**
 * @brief Tokenizes a command string into a list of tokens.
 *
 * @param cmd The command string to be tokenized.
 * @param tokens_list A pointer to the head of the tokens list.
 * @param last_token A pointer to the last token in the list.
 *
 * This function processes a command string and breaks it down into individual
 * tokens, which are then stored in a linked list. It handles spaces,
 * redirections, and other token types appropriately.
 */
void	tokenize_command(char *cmd, t_token **tokens_list, t_token **last_token)
{
	t_token_context		ctx;
	int					current;
	int					start;
	int					is_first_token;

	current = 0;
	is_first_token = 1;
	init_token_context(&ctx, tokens_list, last_token, cmd);
	while (cmd[current])
	{
		while (ft_isspace(cmd[current]))
			current++;
		if (!cmd[current])
			break ;
		start = current;
		if (cmd[current] == '>' || cmd[current] == '<')
			handle_redirection(&ctx, &current);
		else
			handle_token(&ctx, &current, &start, &is_first_token);
	}
	free(ctx.cmd);
}
