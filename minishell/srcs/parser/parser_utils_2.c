/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:37:09 by dherszen          #+#    #+#             */
/*   Updated: 2024/10/10 19:39:30 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate_trim_bounds(const char *input, int start, int len,
int *trim_end)
{
	int	trim_start;

	*trim_end = start + len - 1;
	trim_start = start;
	while (trim_start <= *trim_end && ft_isspace(input[trim_start]))
		trim_start++;
	while (*trim_end > trim_start && ft_isspace(input[*trim_end]))
		(*trim_end)--;
	return (trim_start);
}

t_cmd	*create_segment(const char *input, int start, int len)
{
	t_cmd	*segment;
	int		trim_start;
	int		trim_end;

	segment = malloc(sizeof(t_cmd));
	if (!segment)
		return (NULL);
	init_fd_etc(segment);
	trim_start = calculate_trim_bounds(input, start, len, &trim_end);
	len = trim_end - trim_start + 1;
	if (len <= 0)
	{
		free(segment);
		return (NULL);
	}
	segment->cmd = malloc(len + 1);
	if (!segment->cmd)
	{
		free(segment);
		return (NULL);
	}
	ft_strncpy(segment->cmd, &input[trim_start], len);
	segment->cmd[len] = '\0';
	return (segment);
}

void	init_token_context(t_token_context *ctx, t_token **tokens_list,
t_token **last_token, char *cmd)
{
	ctx->tokens_list = tokens_list;
	ctx->last_token = last_token;
	ctx->cmd = ft_strdup(cmd);
	*tokens_list = NULL;
	*last_token = NULL;
}
