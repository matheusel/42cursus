/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:35:40 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 11:08:06 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_resources(char ***envp, char ***argv, int *fd,
t_shell *shell)
{
	if (envp && *envp)
	{
		free_array(*envp);
		*envp = NULL;
	}
	if (argv && *argv)
	{
		free_array(*argv);
		*argv = NULL;
	}
	dup2(shell->fd[0], STDIN_FILENO);
	dup2(shell->fd[1], STDOUT_FILENO);
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	fd[0] = -1;
	fd[1] = -1;
	if (shell->cmds)
		free_cmd_segments(&shell->cmds);
	if (shell->env_list.head)
		free_env_list(&shell->env_list);
}

int	find_command_path(char **paths, t_token *cmd_token)
{
	char	*command_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		command_path = build_command_path(paths[i], cmd_token->content);
		if (!command_path)
			break ;
		if (access(command_path, X_OK) == 0)
		{
			free(cmd_token->content);
			cmd_token->content = ft_strdup(command_path);
			free_paths(paths);
			free(command_path);
			return (true);
		}
		free(command_path);
	}
	return (false);
}
