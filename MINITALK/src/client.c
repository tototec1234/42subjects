/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torinoue <torinoue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:35:22 by torinoue          #+#    #+#             */
/*   Updated: 2023/10/16 21:55:16 by torinoue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../libft/libft.h"

static void	send_msg(pid_t server_pid, char *msg);
static void	send_char(pid_t server_pid, char c);

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3)
		ft_put_error(">Usage: ./client [server-pid] [message]");
	pid = ft_atoi(argv[1]);
	if (pid < 100 || pid > 99998 || ft_strncmp(ft_itoa(pid), argv[1], \
	ft_strlen(argv[1])) != 0)
	{
		ft_putstr_fd(argv[1], 1);
		ft_put_error(" is not valid pid(100~99998).");
	}
	if (*argv[2])
		send_msg(pid, argv[2]);
	return (0);
}

static void	send_msg(pid_t server_pid, char *msg)
{
	size_t	index;

	index = 0;
	while (msg[index])
		send_char(server_pid, msg[index++]);
}

static void	send_char(pid_t server_pid, char c)
{
	unsigned char	uc;
	size_t			current_bit;
	int				status;

	uc = (unsigned char)c;
	current_bit = 0;
	while (current_bit < CHARACTER_BITS)
	{
		if (uc & (0x01 << current_bit))
			status = kill(server_pid, SIGUSR1);
		else
			status = kill(server_pid, SIGUSR2);
		if (status == -1)
			ft_put_error("Invalid PID.");
		usleep(SLEEP_US);
		current_bit++;
	}
	return ;
}
// ./client 98591 $(python3 -c "print('a'*1025)") 
// ./client 
// $(python3 -c "print('a'*1025)") 
// find [PASS] -type f -print | xargs grep '[STR]'
// find ./ -type f -print | xargs grep 'get_next_line'
// 
// https://medium.com/@oduwoledare/42-minitalk-explained-5b236adc2c24
// 
// test.sh
// 
