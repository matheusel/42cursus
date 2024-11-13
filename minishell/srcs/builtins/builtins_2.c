/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:27:42 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 11:13:14 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_vars(t_env_list *env_list, int output_type);
static int	is_valid_env_key(const char *key);
static int	parse_key_value(char *arg, char **key, char **value);

int	ft_env(t_env_list *env_list)
{
	g_status = 0;
	if (!env_list || !env_list->head)
		return (EXIT_FAILURE);
	print_env_vars(env_list, 0);
	return (EXIT_SUCCESS);
}

int	ft_export(t_env_list *env_list, char *argv[])
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	g_status = 1;
	if (!argv[i])
	{
		print_env_vars(env_list, 1);
		return (EXIT_SUCCESS);
	}
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			if (parse_key_value(argv[i], &key, &value))
				return (EXIT_FAILURE);
			if (!is_valid_env_key(key) || set_env_value(env_list, key, value))
				return (handle_export_error(&key, &value));
			free_key_value(&key, &value);
		}
		i++;
	}
	g_status = 0;
	return (EXIT_SUCCESS);
}

static void	print_env_vars(t_env_list *env_list, int output_type)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (output_type == 1)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

static int	is_valid_env_key(const char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
	{
		ft_putstr_fd("minishell: export: not a valid identifier\n",
			STDERR_FILENO);
		return (false);
	}
	i = 0;
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n",
				STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}

static int	parse_key_value(char *arg, char **key, char **value)
{
	*key = ft_strndup(arg, ft_strchr(arg, '=') - arg);
	*value = ft_strdup(ft_strchr(arg, '=') + 1);
	if (!*key || !*value)
	{
		free_key_value(key, value);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
