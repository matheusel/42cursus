/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:54:07 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 12:32:47 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses the input command string, splits it by pipes, tokenizes
 *        each segment, and fills the argument vectors for each command
 *        segment.
 * @param shell Pointer to the struct with the input command string to be parsed.
 *
 * This function performs the following steps:
 * 1. Counts the number of pipes in the input string.
 * 2. Allocates memory for the command segments.
 * 3. Splits the input string by pipes into command segments.
 * 4. Tokenizes each command segment.
 * 5. Fills the argument vectors for each command segment.
 * 6. Frees the allocated memory for command segments.
 */
void	parse_input(t_shell *shell)
{
	int		pipe_count;

	if (!shell->input || ft_isspace_str(shell->input))
		return ;
	pipe_count = count_pipes(shell->input);
	shell->cmds = ft_calloc((pipe_count + 2), sizeof(t_cmd *));
	if (!shell->cmds)
		return ;
	split_by_pipe(shell->input, shell->cmds);
	tokenize_segments(shell->cmds, pipe_count);
}

/**
 * @brief Initializes the split context structure.
 * @param ctx Pointer to the split context structure to initialize.
 *
 * This function sets the initial values for the split context structure,
 * resetting the start and index to 0, and clearing any single or double
 * quote flags.
 */
static void	init_split_context(t_split_context *ctx)
{
	ctx->start = 0;
	ctx->index = 0;
	ctx->quote_single = 0;
	ctx->quote_double = 0;
}

/**
 * @brief Processes a segment of a piped command.
 * @param input The input command string.
 * @param segments An array of command segments.
 * @param ctx The context for splitting the command.
 * @param current The current position in the input string.
 *
 * This function creates a new command segment from the input string
 * based on the provided context and current position, and adds it to
 * the segments array. It then updates the start position in the context
 * for the next segment.
 */
static void	handle_pipe_segment(const char *input, t_cmd **segments,
t_split_context *ctx, int current)
{
	t_cmd	*new_segment;

	new_segment = create_segment(input, ctx->start, current - ctx->start);
	if (new_segment)
		segments[ctx->index++] = new_segment;
	ctx->start = current + 1;
}

/**
 * @brief Determines if the character should cause a split based on the context.
 * @param c The character to check.
 * @param ctx The context containing the quote states.
 *
 * This function updates the quote state and checks if the character is a pipe
 * that is not within single or double quotes.
 *
 * @return (int) Returns 1 if the character should cause a split, 0 otherwise.
 */
static int	should_split(char c, t_split_context *ctx)
{
	update_quote_state(c, &ctx->quote_single, &ctx->quote_double);
	return (is_pipe(c) && !ctx->quote_single && !ctx->quote_double);
}

/**
 * @brief Splits the input string by pipe ('|') characters and stores the
 *        segments.
 * @param input The input string to be split.
 * @param segments An array of t_cmd pointers where the segments will be stored.
 *
 * This function processes the input string and splits it into segments based
 * on the pipe ('|') characters.
 * Each segment is stored in the provided segments array. The function uses
 * a context structure to keep track of the current state during the splitting
 * process.
 *
 */
void	split_by_pipe(const char *input, t_cmd **segments)
{
	t_split_context	ctx;
	int				current;

	init_split_context(&ctx);
	current = -1;
	while (input[++current])
	{
		if (should_split(input[current], &ctx))
			handle_pipe_segment(input, segments, &ctx, current);
	}
	if (current > ctx.start)
		handle_pipe_segment(input, segments, &ctx, current);
	segments[ctx.index] = NULL;
}
