/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:28 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 19:42:20 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_signal_handler(int sig);
static int	handle_heredoc_input(int fd, char *delim);
static void	handle_heredoc_child(t_shell *shell, t_token *redir_node, int *fd);

/**
 * @brief Handles the heredoc functionality for a given command.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd Pointer to the command structure.
 * @param redir_node Pointer to the redirection token node.
 * @return int Returns EXIT_SUCCESS on success, or EXIT_FAILURE on failure.
 *
 * This function sets up a pipe and forks a child process to handle the
 * heredoc input. It manages signal handling, waits for the child process
 * to complete, and updates the command's input file descriptor with the
 * read end of the pipe. If any errors occur, it returns EXIT_FAILURE.
 */
int	heredoc(t_shell *shell, t_cmd *cmd, t_token *redir_node)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!redir_node->next)
		return (print_syntax_error(PIPE), EXIT_FAILURE);
	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		handle_heredoc_child(shell, redir_node, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	setup_signal_handling();
	if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) != 0))
	{
		g_status = WEXITSTATUS(status);
		close(fd[0]);
		return (EXIT_FAILURE);
	}
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = fd[0];
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles the input for a heredoc, writing to the specified file
 * descriptor.
 *
 * @param fd The file descriptor to write the heredoc input to.
 * @param delim The delimiter string indicating the end of the heredoc input.
 *
 * This function continuously reads input from the user until the delimiter
 * string is encountered or an end-of-file (EOF) condition is met. Each line
 * of input is written to the specified file descriptor. The function ensures
 * that the memory allocated for the input is properly freed.
 *
 * @return Returns EXIT_SUCCESS upon successful completion.
 */
static int	handle_heredoc_input(int fd, char *delim)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, delim) == 0)
			break ;
		else if (input)
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(input);
		}
	}
	if (input)
		free(input);
	return (EXIT_SUCCESS);
}

static void	heredoc_signal_handler(int sig)
{
	g_status = 130;
	if (sig == SIGINT)
		close(STDIN_FILENO);
}

/**
 * @brief Handles the child process for a heredoc operation.
 *
 * @param shell Pointer to the shell structure.
 * @param redir_node Pointer to the redirection token node.
 * @param fd Array of file descriptors for the pipe.
 *
 * This function sets up the signal handling for the heredoc child process,
 * closes the read end of the pipe, processes the heredoc input, closes the
 * write end of the pipe, cleans up resources, and exits with the global
 * status code.
 */
static void	handle_heredoc_child(t_shell *shell, t_token *redir_node, int *fd)
{
	set_heredoc_signal();
	close(fd[0]);
	handle_heredoc_input(fd[1], redir_node->next->content);
	close(fd[1]);
	cleanup_resources(NULL, NULL, shell->fd, shell);
	exit(g_status);
}

void	set_heredoc_signal(void)
{
	int					status;
	struct sigaction	sa1;
	struct sigaction	sa2;

	status = 0;
	sa1.sa_handler = heredoc_signal_handler;
	sa2.sa_handler = SIG_IGN;
	sa1.sa_flags = SA_RESTART;
	sa2.sa_flags = SA_RESTART;
	sigemptyset(&sa1.sa_mask);
	sigemptyset(&sa2.sa_mask);
	sigaddset(&sa1.sa_mask, SIGINT);
	if (sigaction(SIGQUIT, &sa2, NULL) == -1 && !status)
		status = -1;
	if (sigaction(SIGINT, &sa1, NULL) == -1 && !status)
		status = -1;
	if (status == -1)
	{
		perror(__func__);
		exit(EXIT_FAILURE);
	}
}
