/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:40:11 by mc-m-el-          #+#    #+#             */
/*   Updated: 2024/11/12 18:04:05 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Processes the tokens in a command and performs the necessary 
 * redirections.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd Pointer to the command structure containing the tokens list.
 * @return int Returns EXIT_SUCCESS on success, or EXIT_FAILURE on failure.
 *
 * This function iterates through the tokens in the command's tokens list and
 * performs the appropriate redirection based on the token type. It handles
 * input redirection (REDIR_IN), output redirection (REDIR_OUT), append 
 * redirection (REDIR_APPEND), and here-document (HEREDOC). If any redirection 
 * fails, the function returns EXIT_FAILURE. In the case of a here-document 
 * failure, it also updates the global status variable `g_status` unless it is 
 * already set to 130.
 */
int	get_token(t_shell *shell, t_cmd *cmd)
{
	t_token	*token;

	if (!cmd || !cmd->tokens_list)
		return (EXIT_FAILURE);
	token = cmd->tokens_list;
	while (token)
	{
		if (token->type == REDIR_IN && redir_in(cmd, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (token->type == REDIR_OUT
			&& redir_out(cmd, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (token->type == REDIR_APPEND
			&& redir_append(cmd, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (token->type == HEREDOC
			&& heredoc(shell, cmd, token) == EXIT_FAILURE)
		{
			if (g_status != 130)
				g_status = 2;
			return (EXIT_FAILURE);
		}
		token = token->next;
	}
	return (EXIT_SUCCESS);
}
