/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erros.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:35:31 by mc-m-el-          #+#    #+#             */
/*   Updated: 2024/04/02 20:23:18 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	exit_error(int num)
{
	if (num == 1)
		ft_printf("Error! Using: ./fdf Archive.\n");
	else if (num == 2)
		ft_printf("Error! Invalid Archive.\n");
	else if (num == 3)
		ft_printf("Error! Invalid Map.\n");
	return (-1);
}