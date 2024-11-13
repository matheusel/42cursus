/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:18:47 by mc-m-el-          #+#    #+#             */
/*   Updated: 2024/11/12 17:09:03 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

// heredoc_1.c
int		heredoc(t_shell *shell, t_cmd *cmd, t_token *redir_node);
void	set_heredoc_signal(void);

// heredoc_2.c
t_split	*split_to_expand(const char *line);
char	*expand_split_list_here(t_split **list, t_env_list *env_list);

#endif
