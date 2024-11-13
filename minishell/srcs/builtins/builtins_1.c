/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:48:45 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 20:06:08 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_to_home(t_env_list *env_list);
static int	change_to_oldpwd(t_env_list *env_list);
static char	*expand_tilde(const char *path, t_env_list *env_list);

int	ft_cd(t_env_list *env_list, char **args)
{
	char	*oldpwd;
	char	*path;

	g_status = 1;
	oldpwd = getcwd(NULL, 0);
	if (get_array_size(args) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	if (!args[1] || !ft_strcmp(args[1], "~"))
		return (free(oldpwd), change_to_home(env_list));
	else if (!ft_strcmp(args[1], "-"))
		return (free(oldpwd), change_to_oldpwd(env_list));
	path = expand_tilde(args[1], env_list);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		free_and_set_env_dirs(&oldpwd, &path, env_list);
		return (EXIT_FAILURE);
	}
	free_and_set_env_dirs(&oldpwd, &path, env_list);
	g_status = 0;
	return (EXIT_SUCCESS);
}

int	ft_echo(char **args)
{
	int	n;
	int	newline;

	n = 1;
	newline = 1;
	if (args[n] && !ft_strcmp(args[n], "-n"))
	{
		newline = 0;
		n++;
	}
	while (args[n])
	{
		ft_putstr_fd(args[n], STDOUT_FILENO);
		if (args[n + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		n++;
	}
	ft_putstr_fd(args[n], STDOUT_FILENO);
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_status = 0;
	return (EXIT_SUCCESS);
}

static int	change_to_home(t_env_list *env_list)
{
	const char	*home;

	home = getenv_ll(env_list, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	chdir(home);
	return (EXIT_SUCCESS);
}

static int	change_to_oldpwd(t_env_list *env_list)
{
	const char	*oldpwd;

	oldpwd = getenv_ll(env_list, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	chdir(oldpwd);
	return (EXIT_SUCCESS);
}

static char	*expand_tilde(const char *path, t_env_list *env_list)
{
	const char	*home;
	char		*expanded_path;

	if (path[0] != '~')
		return (ft_strdup(path));
	home = getenv_ll(env_list, "HOME");
	if (!home)
		return (ft_strdup(path));
	expanded_path = malloc(strlen(home) + strlen(path));
	if (!expanded_path)
		return (NULL);
	ft_strcpy(expanded_path, home);
	ft_strcat(expanded_path, path + 1);
	return (expanded_path);
}
