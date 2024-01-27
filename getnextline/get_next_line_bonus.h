/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:30 by mc-m-el           #+#    #+#             */
/*   Updated: 2024/01/13 14:56:32 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_strlen(char *str);
int		ft_strlen_n(char *str);
int		confirm_n(char *buffer);
char	*ft_strjoin(char *buffer, char *line);
char	*find_n(char *buffer, int n);
char	*find_buffer(char *buffer, int n, int count);
char	*hunter_str(int fd);
char	*get_next_line(int fd);

#endif
