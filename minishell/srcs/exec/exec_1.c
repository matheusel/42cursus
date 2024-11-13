/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:33:56 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 14:10:54 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_commands_loop(t_shell *shell, t_fork_args *args);
static int	process_command(t_shell *shell, t_fork_args *args, int i);
static int	handle_single_builtin(t_shell *shell);
static void	handle_fork(t_cmd *cmd, t_shell *shell, t_fork_args *args, int i);

void	execute_command(t_shell *shell)
{
	t_fork_args	args;

	if (!shell->cmds || handle_single_builtin(shell))
		return ;
	args.envp = env_list_to_array(&shell->env_list);
	if (!args.envp)
	{
		perror(__func__);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	execute_commands_loop(shell, &args);
	wait_processes(shell);
	setup_signal_handling();
	if (args.envp)
		free_array(args.envp);
	free_cmd_segments(&shell->cmds);
}

static void	execute_commands_loop(t_shell *shell, t_fork_args *args)
{
	int	i;

	i = -1;
	while (shell->cmds[++i])
	{
		if (get_cmd_token(shell->cmds[i]) && process_command(shell, args, i))
			continue ;
	}
}

static int	process_command(t_shell *shell, t_fork_args *args, int i)
{
	t_token	*cmd_token;

	cmd_token = get_cmd_token(shell->cmds[i]);
	if (!cmd_token)
		return (EXIT_FAILURE);
	set_command_path(cmd_token, &shell->env_list);
	if (pipe(args->fd) == -1)
	{
		perror(__func__);
		return (EXIT_FAILURE);
	}
	args->argv = fill_argv(shell->cmds[i]);
	if (!args->argv)
		return (EXIT_FAILURE);
	if (!cmd_token->content)
	{
		perror(__func__);
		free_array(args->argv);
		return (EXIT_FAILURE);
	}
	handle_fork(shell->cmds[i], shell, args, i);
	free_array(args->argv);
	return (EXIT_SUCCESS);
}

static int	handle_single_builtin(t_shell *shell)
{
	char	**argv;
	int		builtin;

	if (!has_pipe(shell) && get_cmd_token(shell->cmds[0])
		&& is_builtin(get_cmd_token(shell->cmds[0])->content) != EXIT_FAILURE)
	{
		builtin = is_builtin(get_cmd_token(shell->cmds[0])->content);
		argv = fill_argv(shell->cmds[0]);
		if (!argv)
			return (true);
		if (shell->cmds[0]->fd_in != -1)
			dup2(shell->cmds[0]->fd_in, STDIN_FILENO);
		if (shell->cmds[0]->fd_out != -1)
			dup2(shell->cmds[0]->fd_out, STDOUT_FILENO);
		execute_builtin(builtin, &shell->env_list, argv, shell);
		free_array(argv);
		return (true);
	}
	return (false);
}

static void	handle_fork(t_cmd *cmd, t_shell *shell, t_fork_args *args, int i)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror(__func__);
		if (args->argv)
			free_array(args->argv);
		return ;
	}
	if (cmd->pid == 0)
	{
		if (shell->cmds[i]->fd_in != -1)
		{
			if (dup2(shell->cmds[i]->fd_in, STDIN_FILENO) == -1)
			{
				perror(__func__);
				exit(EXIT_FAILURE);
			}
		}
		handle_redir_out(shell, i, args);
		close(args->fd[0]);
		close(args->fd[1]);
		execute_child_process(shell, args->argv, args->envp);
	}
	else
		handle_parent_process(cmd, args);
}
