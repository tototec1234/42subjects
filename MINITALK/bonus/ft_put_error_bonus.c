/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torinoue <torinoue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:56:00 by torinoue          #+#    #+#             */
/*   Updated: 2023/10/16 22:58:51 by torinoue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"
#include "../libft/libft.h"

void	ft_put_error_bonus(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
	return ;
}
