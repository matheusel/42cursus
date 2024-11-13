/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:17:35 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 16:24:00 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_cmd_token(t_cmd *cmd)
{
	t_token	*token;

	if (!cmd || !cmd->tokens_list)
		return (NULL);
	token = cmd->tokens_list;
	while (token)
	{
		if (token->type == CMD)
			return (token);
		token = token->next;
	}
	return (NULL);
}

void	set_command_path(t_token *cmd_token, t_env_list *env_list)
{
	char		*path_env;
	char		**paths;
	struct stat	p_stat;

	if (is_builtin(cmd_token->content) != EXIT_FAILURE)
		return ;
	if (access(cmd_token->content, F_OK) != 0 && *cmd_token->content == '.')
		return ;
	if (stat(cmd_token->content, &p_stat) == 0 && !S_ISDIR(p_stat.st_mode))
	{
		if (access(cmd_token->content, F_OK | X_OK) == 0)
			return ;
		else if (access(cmd_token->content, F_OK | X_OK) != 0
			&& *cmd_token->content == '.')
			return ;
	}
	path_env = getenv_ll(env_list, "PATH");
	if (!path_env)
		return ;
	paths = fill_paths(path_env, count_paths(path_env));
	if (!find_command_path(paths, cmd_token))
		free_paths(paths);
}

// put in libft, if not there already
void	free_array(char **arg)
{
	int	i;

	if (!arg)
		return ;
	i = -1;
	while (arg[++i])
	{
		free(arg[i]);
		arg[i] = NULL;
	}
	free(arg);
	arg = NULL;
}

char	*build_command_path(const char *dir, const char *cmd)
{
	char	*path;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	path = malloc(len);
	if (!path)
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}

char	**free_and_return(char **array, char **return_value)
{
	free_paths(array);
	return (return_value);
}
