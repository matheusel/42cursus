/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:14:57 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 19:41:20 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "structs.h"
# include "builtins.h"
# include "var_exp.h"
# include <errno.h> // errno variable
# include "heredoc.h"
# include "redirects.h"
# include <linux/limits.h> // MAX_PATH macro
# include <stdbool.h> // bool type: true, false
# include "exec.h"
# include <sys/stat.h> // stat function
# include <stdlib.h> // malloc, free
# include <signal.h> // signal and sigaction functions
# include <sys/wait.h> // waitpid function
# include <stdio.h> // printf
# include <unistd.h> // write, access, pipe, fork, dup2, execve functions
# include <fcntl.h> // open, close functions

//Readline library
# include <readline/readline.h>
# include <readline/history.h>

extern volatile int	g_status;

// main.c // depois tirar?
void		print_segments(t_cmd **segments);

// signal_handling.c
void		setup_signal_handling(void);
void		signal_handle(int sig);
void		handle_sig_error(int sig);

// errors_validations_1.c
int			is_operator(const char *str);
int			is_valid_input(const char *input);
int			check_input_errors(const char *input);
int			check_quotes_errors(const char *input);
int			check_pipes_errors(const char *input);

// errors_validations_2.c
int			is_closed_quote(const char *str);
int			print_syntax_error(int type);

// errors_validations_3.c
int			is_redirection(char c);
int			check_operator_sequence(const char *str);
int			handle_quotes(const char *input, int *i, int *in_quotes,
				char *closing_quote);

// parser_1.c
void		parse_input(t_shell *shell);
void		split_by_pipe(const char *input, t_cmd **segments);

// parser_2.c
void		tokenize_segments(t_cmd **segments, int pipe_count);
void		tokenize_command(char *cmd, t_token **tokens_list,
				t_token **last_token);

// parser_3.c
void		handle_redirection(t_token_context *ctx, int *current);
void		handle_redirection_argument(t_token_context *ctx, int *current,
				t_token_type arg_type);

// parser_utils_1.c
int			is_simple_quote(char c);
int			is_double_quote(char c);
int			is_pipe(char c);
void		update_quote_state(char c, int *single_quote_state,
				int *double_quote_state);
int			count_pipes(const char *input);

// parser_utils_2.c
t_cmd		*create_segment(const char *input, int start, int len);
void		init_token_context(t_token_context *ctx, t_token **tokens_list,
				t_token **last_token, char *cmd);

// parser_utils_3.c
void		free_cmd_segments(t_cmd ***segments);
void		free_tokens(t_token *tokens_list);
void		add_token(t_token_context *ctx, int start, int end,
				t_token_type type);
void		init_fd_etc(t_cmd *segment);

// env_utils_1.c
size_t		get_array_size(char **envp);
char		*get_envp_key(char *env);
char		*get_envp_value(char *env);
t_env_node	*create_node(const char *key, const char *value);
void		add_env_node(t_env_list *env_list, t_env_node *new);

// env_utils_2.c
void		init_env(char **envp, t_env_list *env_list);
void		free_env_list(t_env_list *env_list);
char		*getenv_ll(t_env_list *env_list, const char *key);
int			set_env_value(t_env_list *env_list, const char *key,
				const char *value);
size_t		env_lst_size(t_env_list *env_lst);

// env_utils_3.c
void		*free_my_envp(char **envp);
char		**env_list_to_array(t_env_list *env_list);
int			delete_env_node(t_env_list *env_list, const char *key);
void		free_key_value(char **key, char **value);

// env_utils_4.c
int			handle_export_error(char **key, char **value);
const char	**split_path_value(const char *value);
int			count_paths(const char *value);
char		**fill_paths(const char *value, int count);
int			fill_paths_loop(const char *value, char **paths);

// env_utils_5.c
void		free_paths(char **paths);
char		**allocate_paths(int count);
char		*allocate_and_copy_path(const char *start, int length);
void		free_paths_on_error(char **paths, int i);
void		free_env_on_error(t_env_list **env_list, char **key, char **value);

#endif
