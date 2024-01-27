/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el <mc-m-el-@student.42.rio>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:01:54 by mc-m-el-          #+#    #+#             */
/*   Updated: 2023/12/12 20:53:38 by mc-m-el          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *format, ...);
int	ft_printchar(char c);
int	ft_printstr(char *s);
int	ft_printdiu(int n, char c);
size_t	ft_strlen(const char *s);
int	ft_printpointer(void *p);
int	ft_printxxp(unsigned long n, char c);

#endif
