/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torinoue <torinoue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:43:53 by torinoue          #+#    #+#             */
/*   Updated: 2023/10/19 17:59:32 by torinoue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../libft/libft.h"

t_char	g_char;

static void	init_char(void);
static void	establish_handler(void);
static void	catch_signal(int signum, siginfo_t *info, void *ctx);
static void	init_char(void);

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		ft_put_error("No argument is required.\n");
	ft_putstr_fd(">server pid:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	establish_handler();
	while (1)
		pause();
	return (0);
}

static void	establish_handler(void)
{
	struct sigaction	sa_siguser;

	init_char();
	ft_bzero(&sa_siguser, sizeof(sa_siguser));
	sa_siguser.sa_sigaction = catch_signal;
	sa_siguser.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_siguser, NULL) == -1 \
	|| sigaction(SIGUSR2, &sa_siguser, NULL) == -1)
		ft_put_error("signal error\n");
}

static void	catch_signal(int signum, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	if (signum == SIGUSR1)
		g_char.letter |= 1 << g_char.current_bit;
	g_char.current_bit++;
	if (g_char.current_bit == CHARACTER_BITS)
	{
		ft_putchar_fd(g_char.letter, 1);
		init_char();
	}
	return ;
}

static void	init_char(void)
{
	g_char.current_bit = 0;
	g_char.letter = 0;
	return ;
}
