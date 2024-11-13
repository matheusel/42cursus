/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:29:08 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/11 16:26:15 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//exec_1.c
void	execute_command(t_shell *shell);

//exec_2.c
void	execute_child_process(t_shell *shell, char **argv, char **envp);
void	handle_parent_process(t_cmd *cmd, t_fork_args *args);
void	wait_processes(t_shell *shell);
void	handle_redir_out(t_shell *shell, int i, t_fork_args *args);

// exec_utils_1.c
t_token	*get_cmd_token(t_cmd *cmd);
void	set_command_path(t_token *cmd_token, t_env_list *env_list);
void	free_array(char **arg);
char	*build_command_path(const char *dir, const char *cmd);
char	**free_and_return(char **array, char **return_value);

// exec_utils_2.c
char	**fill_argv(t_cmd *cmd);
int		count_paths(const char *value);
char	*get_error(void);
bool	has_pipe(t_shell *shell);

// exec_utils_3.c
void	cleanup_resources(char ***envp, char ***argv, int *fd,
			t_shell *shell);
int		find_command_path(char **paths, t_token *cmd_token);

#endif
