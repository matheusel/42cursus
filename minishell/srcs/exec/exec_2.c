/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:04:25 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 16:25:52 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_process(t_shell *shell, char **argv, char **envp)
{
	int			builtin;
	struct stat	p_stat;

	signal(SIGINT, SIG_DFL);
	builtin = is_builtin(argv[0]);
	if (builtin != EXIT_FAILURE)
	{
		execute_builtin(builtin, &shell->env_list, argv, shell);
		cleanup_resources(&envp, &argv, shell->fd, shell);
		exit(EXIT_SUCCESS);
	}
	if (stat(argv[0], &p_stat) != 0 || S_ISDIR(p_stat.st_mode))
	{
		ft_putstr_fd(get_error(), STDERR_FILENO);
		cleanup_resources(&envp, &argv, shell->fd, shell);
		exit(127);
	}
	if (execve(argv[0], argv, envp) == -1)
	{
		ft_putstr_fd(get_error(), STDERR_FILENO);
		cleanup_resources(&envp, &argv, shell->fd, shell);
		exit(EXIT_FAILURE);
	}
}

void	handle_parent_process(t_cmd *cmd, t_fork_args *args)
{
	if ((cmd + 1) != NULL)
	{
		if (dup2(args->fd[0], STDIN_FILENO) == -1)
			perror(__func__);
	}
	close(args->fd[0]);
	close(args->fd[1]);
}

void	wait_processes(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (shell->cmds[i + 1] != NULL)
		i++;
	waitpid(shell->cmds[i]->pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
	while (wait (NULL) > 0)
		continue ;
}

void	handle_redir_out(t_shell *shell, int i, t_fork_args *args)
{
	if (shell->cmds[i]->fd_out != -1)
	{
		if (dup2(shell->cmds[i]->fd_out, STDOUT_FILENO) == -1)
		{
			perror(__func__);
			exit(EXIT_FAILURE);
		}
	}
	else if (shell->cmds[i + 1] != NULL)
	{
		if (dup2(args->fd[1], STDOUT_FILENO) == -1)
		{
			perror(__func__);
			exit(EXIT_FAILURE);
		}
	}
}
