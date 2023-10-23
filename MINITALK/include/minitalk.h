/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torinoue <torinoue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:54:11 by torinoue          #+#    #+#             */
/*   Updated: 2023/10/17 03:22:53 by torinoue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sysexits.h>
# define EOT 4
# define SLEEP_US 200
# ifndef CHARACTER_BITS
#  define CHARACTER_BITS 8
# endif

typedef struct s_char
{
	int				current_bit;
	unsigned short	letter;
}	t_char;

void	ft_put_error(char *str);

#endif

// if you want to handle multi-byte characters (e.g., 16-bit characters):
// #define CHARACTER_BITS 16
