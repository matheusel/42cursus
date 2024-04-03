/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:40 by mc-m-el           #+#    #+#             */
/*   Updated: 2024/04/02 20:19:02 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_strlenx(char *str);
int		ft_strlen_n(char *str);
int		confirm_n(char *buffer);
char	*ft_strjoinx(char *buffer, char *line);
char	*find_n(char *buffer, int n);
char	*find_buffer(char *buffer, int n, int count);
char	*hunter_str(int fd);
char	*get_next_line(int fd);

#endif
