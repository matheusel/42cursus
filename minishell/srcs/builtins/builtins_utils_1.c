/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:44:55 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 19:06:12 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (EXIT_FAILURE);
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	else if (!ft_strcmp(cmd, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd, "env"))
		return (ENV);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	else
		return (EXIT_FAILURE);
}

int	execute_builtin(int builtin, t_env_list *env_list, char **args,
t_shell *shell)
{
	if (builtin == ECHO)
		return (ft_echo(args));
	else if (builtin == CD)
		return (ft_cd(env_list, args));
	else if (builtin == PWD)
		return (ft_pwd(args));
	else if (builtin == ENV)
		return (ft_env(env_list));
	else if (builtin == UNSET)
		return (ft_unset(env_list, args));
	else if (builtin == EXPORT)
		return (ft_export(env_list, args));
	else if (builtin == EXIT)
		return (ft_exit(env_list, args, shell));
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	free_and_set_env_dirs(char **oldpwd, char **path, t_env_list *env_list)
{
	set_env_dirs(env_list, *oldpwd);
	free(*oldpwd);
	free(*path);
}

void	set_env_dirs(t_env_list *env_list, char *oldpwd)
{
	char	*current_pwd;

	set_env_value(env_list, "OLDPWD", oldpwd);
	current_pwd = getcwd(NULL, 0);
	set_env_value(env_list, "PWD", current_pwd);
	free(current_pwd);
}
