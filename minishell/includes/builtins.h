/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:08:55 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 19:01:17 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// builtins_1.c
int			ft_cd(t_env_list *env_list, char **args);
int			ft_echo(char **arg);

// builtins_2.c
int			ft_env(t_env_list *env_list);
int			ft_export(t_env_list *env_list, char *argv[]);

// builtins_3.c
int			ft_unset(t_env_list *env_list, char *argv[]);
int			ft_pwd(char **args);
int			ft_exit(t_env_list *env_list, char **args, t_shell *shell);

// builtins_utils_1.c
int			is_builtin(const char *cmd);
int			execute_builtin(int builtin, t_env_list *env_list, char **args,
				t_shell *shell);
void		free_and_set_env_dirs(char **oldpwd, char **path,
				t_env_list *env_list);
void		set_env_dirs(t_env_list *env_list, char *oldpwd);

#endif
