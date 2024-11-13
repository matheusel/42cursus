/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:50:19 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 11:13:30 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env_list *env_list, char *argv[])
{
	int	i;

	i = 0;
	g_status = 0;
	while (argv[++i])
	{
		if (delete_env_node(env_list, argv[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_pwd(char **args)
{
	char	cwd[PATH_MAX];
	size_t	length;

	(void)args;
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("minishell: pwd");
		g_status = 1;
		return (EXIT_FAILURE);
	}
	length = ft_strlen(cwd);
	ft_strlcat(&cwd[length], "\n", 2);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	g_status = 0;
	return (EXIT_SUCCESS);
}

static int	is_numeric(const char *str);
static void	handle_exit_argument(char *arg);

int	ft_exit(t_env_list *env_list, char **args, t_shell *shell)
{
	if (get_array_size(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_status = 1;
		return (EXIT_FAILURE);
	}
	if (args[1])
		handle_exit_argument(args[1]);
	free(shell->input);
	rl_clear_history();
	if (shell->cmds)
		free_cmd_segments(&shell->cmds);
	if (shell->env_list.head)
		free_env_list(&shell->env_list);
	free_env_list(env_list);
	free_array(args);
	if (shell->fd[0] != -1)
		close(shell->fd[0]);
	if (shell->fd[1] != -1)
		close(shell->fd[1]);
	exit(g_status);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_exit_argument(char *arg)
{
	if (is_numeric(arg))
		g_status = ft_atoi(arg);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_status = 2;
	}
}
