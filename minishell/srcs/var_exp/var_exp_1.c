/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:54:51 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 19:43:18 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_split_list(t_split **list, t_shell *shell);
static void	replace_str(char **str, char *new_str);

/**
 * @brief Expands variables in the token list of each command in the shell.
 * @param shell Pointer to the shell structure containing the commands and
 * environment.
 *
 * This function iterates through each command in the shell, and for each token
 * in the command's token list, it performs variable expansion if the token type
 * is CMD, CMD_ARG, IN_ARG, OUT_ARG, or APPEND_ARG. The expanded content is then
 * printed for debugging purposes.
 */
void	expand_var(t_shell *shell)
{
	int		i;
	t_token	*token;

	i = -1;
	if (!shell->cmds)
		return ;
	while (shell->cmds[++i])
	{
		token = shell->cmds[i]->tokens_list;
		while (token)
		{
			if (token->type == HEREDOC_ARG)
				token->content = remove_surrounding_quotes(token->content);
			else
				token->content = complex_expansion(token->content, shell);
			token = token->next;
		}
	}
}

/**
 * @brief Performs simple variable expansion on a given string.
 * @param content The string to be expanded.
 * @param shell Pointer to the shell structure containing the environment.
 * @return The expanded string.
 *
 * This function takes a string and performs simple variable expansion based
 * on the environment variables stored in the shell. It returns the expanded
 * string.
 */
char	*simple_expansion(char *input, t_shell *shell)
{
	t_split	*split;

	if (!*input)
		return (input);
	split = split_by_group(input);
	free(input);
	if (!split)
	{
		perror(__func__);
		exit(EXIT_FAILURE);
	}
	return (expand_split_list(&split, shell));
}

/**
 * @brief Performs complex variable expansion on a given string.
 * @param content The string to be expanded.
 * @param shell Pointer to the shell structure containing the environment.
 * @return The expanded string.
 *
 * This function takes a string and performs complex variable expansion based
 * on the environment variables stored in the shell. It returns the expanded
 * string.
 */
char	*complex_expansion(char *input, t_shell *shell)
{
	t_split	*tmp;
	t_split	*split;

	split = split_by_quote_group(input);
	free(input);
	if (!split)
	{
		perror(__func__);
		exit(EXIT_FAILURE);
	}
	tmp = split;
	while (tmp)
	{
		if (*tmp->str == '\'')
			tmp->str = remove_surrounding_quotes(tmp->str);
		else
		{
			tmp->str = remove_surrounding_quotes(tmp->str);
			tmp->str = simple_expansion(tmp->str, shell);
		}
		tmp = tmp->next;
	}
	return (t_split_to_str(&split));
}

/**
 * @brief Expands variables in a linked list of split nodes.
 * @param list A pointer to the linked list of split nodes.
 * @param shell Pointer to the shell structure containing the environment and
 * exit status.
 * @return The expanded string.
 *
 * This function iterates through a linked list of split nodes and performs
 * variable expansion. If a node contains the special variable "$?", it is
 * replaced with the shell's exit status. If a node contains a variable
 * starting with "$", it is replaced with the corresponding environment
 * variable value. The function returns the expanded string.
 */
static char	*expand_split_list(t_split **list, t_shell *shell)
{
	t_split	*tmp;
	char	*expanded;

	tmp = *list;
	while (tmp)
	{
		expanded = NULL;
		if (ft_strcmp(tmp->str, "$?") == 0)
			replace_str(&tmp->str, ft_itoa(g_status));
		else if (tmp->str[0] == '$' && tmp->str[1])
		{
			expanded = getenv_ll(&shell->env_list, tmp->str + 1);
			free(tmp->str);
			if (expanded)
				tmp->str = ft_strdup(expanded);
			else
				tmp->str = ft_strdup("");
			if (!tmp->str)
				exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (t_split_to_str(list));
}

static void	replace_str(char **str, char *new_str)
{
	free(*str);
	*str = new_str;
}
