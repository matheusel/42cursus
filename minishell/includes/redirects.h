/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:39:38 by mc-m-el-          #+#    #+#             */
/*   Updated: 2024/11/12 17:47:44 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

// redirect_1.c
int	redirect(t_shell *shell);
int	redir_in(t_cmd *sentence, t_token *redir_node);
int	redir_append(t_cmd *sentence, t_token *redir_node);
int	redir_out(t_cmd *sentence, t_token *redir_node);

// redirect_1.c
int	get_token(t_shell *shell, t_cmd *cmd);

#endif
