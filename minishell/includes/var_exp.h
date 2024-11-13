/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:28:03 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 17:08:57 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXP_H
# define VAR_EXP_H

// var_exp_1.c
void	expand_var(t_shell *shell);
char	*simple_expansion(char *input, t_shell *shell);
char	*complex_expansion(char *input, t_shell *shell);

// var_exp_utils_1.c
char	*remove_surrounding_quotes(char *str);
t_split	*split_by_quote_group(const char *str);

// var_exp_utils_2.c
t_split	*split_by_group(const char *str);
char	*copy_quote(const char *str);
char	*copy_space(const char *str);
char	*copy_token(const char *str);
char	*copy_var(const char *str);

// var_exp_utils_3.c
void	free_split_list(t_split *list);
t_split	*new_split_node(char *content);
void	append(t_split **head, t_split *node);
char	*t_split_to_str(t_split **head);

#endif
