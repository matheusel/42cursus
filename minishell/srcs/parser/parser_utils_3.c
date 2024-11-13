/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:54:48 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 10:02:31 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_segments(t_cmd ***segments)
{
	int	i;

	if (!segments || !*segments)
		return ;
	i = -1;
	while ((*segments)[++i])
	{
		if ((*segments)[i]->fd_in != -1)
			close((*segments)[i]->fd_in);
		if ((*segments)[i]->fd_out != -1)
			close((*segments)[i]->fd_out);
		free_tokens((*segments)[i]->tokens_list);
		(*segments)[i]->tokens_list = NULL;
		free((*segments)[i]->cmd);
		(*segments)[i]->cmd = NULL;
		free((*segments)[i]);
		(*segments)[i] = NULL;
	}
	free(*segments);
	*segments = NULL;
}

void	free_tokens(t_token *tokens_list)
{
	t_token	*current;
	t_token	*next;

	current = tokens_list;
	while (current)
	{
		next = current->next;
		free(current->content);
		current->content = NULL;
		current->prev = NULL;
		current->next = NULL;
		free(current);
		current = next;
	}
}

void	add_token(t_token_context *ctx, int start, int end, t_token_type type)
{
	t_token	*new_token;
	int		length;

	length = end - start;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->content = malloc(length + 1);
	if (!new_token->content)
	{
		free(new_token);
		return ;
	}
	ft_strncpy(new_token->content, ctx->cmd + start, length);
	new_token->content[length] = '\0';
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = *ctx->last_token;
	if (*ctx->last_token)
		(*ctx->last_token)->next = new_token;
	else
		*ctx->tokens_list = new_token;
	*ctx->last_token = new_token;
}

void	init_fd_etc(t_cmd *segment)
{
	segment->cmd = NULL;
	segment->fd_in = -1;
	segment->fd_out = -1;
	segment->pid = -1;
	segment->should_execute = 1;
	segment->tokens_list = NULL;
}
