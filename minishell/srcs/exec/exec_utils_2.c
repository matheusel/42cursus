/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:03:14 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 14:47:45 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	allocate_argv(char ***argv, int argc);
//static void	free_argv(char **argv, int count);
static int	count_n_args(t_token *token);

/**
 * @brief Fills the argv array of a t_cmd structure with command and argument
 *        tokens.
 * @param cmd Pointer to the t_cmd structure whose argv array is to be filled.
 *
 * This function allocates memory for the argv array based on the number of
 * command and argument tokens in the tokens_list of the t_cmd structure. It
 * then iterates through the tokens_list, copying the content of each CMD or
 * CMD_ARG token into the argv array. If memory allocation fails at any point,
 * the function frees any previously allocated memory and sets the argv pointer
 * to NULL.
 */

char	**fill_argv(t_cmd *cmd)
{
	t_token	*current_token;
	char	**argv;
	int		i;

	if (!allocate_argv(&argv, count_n_args(cmd->tokens_list)))
		return (NULL);
	current_token = cmd->tokens_list;
	i = 0;
	while (current_token)
	{
		if (current_token->type == CMD || current_token->type == CMD_ARG)
		{
			argv[i] = ft_strdup(current_token->content);
			if (!argv[i])
			{
				free_array(argv);
				return (NULL);
			}
			i++;
		}
		current_token = current_token->next;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * @brief Allocates memory for an array of strings (argv).
 *
 * @param argv Pointer to the array of strings to be allocated.
 * @param argc Number of strings to allocate space for.
 * @return Returns 1 if the allocation is successful, otherwise returns 0.
 *
 * This function allocates memory for an array of strings (argv) with a size
 * sufficient to hold 'argc' number of strings plus one additional element
 * for a NULL terminator. The allocated memory is assigned to the pointer
 * provided by the caller.
 */
static int	allocate_argv(char ***argv, int argc)
{
	*argv = malloc((argc + 1) * sizeof(char *));
	return (*argv != NULL);
}

/**
 * @brief Frees a dynamically allocated array of strings.
 *
 * @param argv The array of strings to be freed.
 * @param count The number of strings in the array.
 *
 * This function iterates through an array of strings and frees each string,
 * then frees the array itself.
 */
/* static void	free_argv(char **argv, int count)
{
	while (--count >= 0)
		free(argv[count]);
	free(argv);
} */

/**
 * @brief Counts the number of command and command argument tokens in a linked
 *        list.
 *
 * @param token A pointer to the head of the linked list of tokens.
 *
 * This function iterates through a linked list of tokens and counts how many of
 * them are of type CMD or CMD_ARG.
 * @return The number of tokens that are of type CMD or CMD_ARG.
 */
static int	count_n_args(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == CMD || token->type == CMD_ARG)
			count++;
		token = token->next;
	}
	return (count);
}

char	*get_error(void)
{
	static char	message[1000];

	ft_strcpy(message, "minishell: ");
	if (errno == ENOENT)
		return ("minishell: command not found\n");
	ft_strcat(message, strerror(errno));
	ft_strcat(message, "\n");
	return (message);
}

bool	has_pipe(t_shell *shell)
{
	int	i;

	if (!shell->cmds)
		return (false);
	i = -1;
	while (shell->cmds[++i])
		continue ;
	return (i > 1);
}
