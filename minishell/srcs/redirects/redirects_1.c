/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:40:11 by mc-m-el-          #+#    #+#             */
/*   Updated: 2024/11/13 12:03:37 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles output redirection for a command.
 *
 * @param content The command structure containing file descriptors.
 * @param redir_node The redirection token node.
 * @return int Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 *
 * This function manages the output redirection for a command by opening the
 * specified file and updating the command's output file descriptor. If the
 * redirection node does not have a next node, it prints a syntax error and
 * sets the global status to 2. If the file cannot be opened, it prints an
 * error message and returns EXIT_FAILURE.
 */
int	redir_out(t_cmd *content, t_token *redir_node)
{
	int	fd;

	if (!redir_node->next)
	{
		print_syntax_error(PIPE);
		g_status = 2;
		return (EXIT_FAILURE);
	}
	if (content->fd_out != -1)
		close(content->fd_out);
	fd = open(redir_node->next->content, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	content->fd_out = fd;
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles input redirection for a command.
 *
 * @param content Pointer to the command structure.
 * @param redir_node Pointer to the redirection token node.
 * @return int Returns EXIT_SUCCESS on success, or EXIT_FAILURE on error.
 *
 * This function manages the input redirection for a given command. It checks
 * if the next token exists, prints a syntax error if it doesn't, and updates
 * the global status. It then closes the current input file descriptor if it
 * is open, and opens the file specified in the next token with read-only mode.
 * If the file cannot be opened, it prints an error message and returns
 * EXIT_FAILURE. On success, it updates the command's input file descriptor
 * and returns EXIT_SUCCESS.
 */
int	redir_in(t_cmd *content, t_token *redir_node)
{
	int	fd;

	if (!redir_node->next)
	{
		print_syntax_error(PIPE);
		g_status = 2;
		return (EXIT_FAILURE);
	}
	if (content->fd_in != -1)
		close(content->fd_in);
	fd = open(redir_node->next->content, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	content->fd_in = fd;
	return (EXIT_SUCCESS);
}
/**
 * @brief Handles input redirection for a command.
 *
 * @param content Pointer to the command structure.
 * @param redir_node Pointer to the redirection token node.
 * @return int Returns EXIT_SUCCESS on success, or EXIT_FAILURE on error.
 * This function manages the input redirection for a given command. It first
 * This function handles the append redirection (>>) for a command. It checks
 * if the next token exists, prints a syntax error if it doesn't, and updates
 * the global status. It then closes the current output file descriptor if it
 * is open, and opens the file specified in the next token with append mode.
 * If the file cannot be opened, it prints an error message and returns
 * EXIT_FAILURE. On success, it updates the command's output file descriptor
 * and returns EXIT_SUCCESS.
 */

int	redir_append(t_cmd *content, t_token *redir_node)
{
	int	fd;

	if (!redir_node->next)
	{
		print_syntax_error(PIPE);
		g_status = 2;
		return (EXIT_FAILURE);
	}
	if (content->fd_out != -1)
		close(content->fd_out);
	fd = open(redir_node->next->content, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	content->fd_out = fd;
	return (EXIT_SUCCESS);
}
/**
 * @brief Processes and redirects commands in the shell.
 *
 * @param shell Pointer to the shell structure containing command information.
 * @return int Returns EXIT_SUCCESS on success, or EXIT_FAILURE on error.
 *
 * This function iterates through the commands in the shell structure and
 * processes each command using the get_token function. If any command
 * processing fails, the function returns EXIT_FAILURE. Otherwise, it returns
 * EXIT_SUCCESS.
 */

int	redirect(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->cmds[++i])
	{
		if (get_token(shell, shell->cmds[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
