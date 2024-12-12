/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos <msantos@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:23:08 by msantos           #+#    #+#             */
/*   Updated: 2024/12/12 15:49:36 by msantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig, siginfo_t *info)
{
	static char		c = 0;
	static int		bit = 0;
	static pid_t	client = 0;

	if (info->si_pid)
		client = info->si_pid;
	if (SIGUSR1 == sig)
		c |= (0x80 >> bit);
	else if (SIGUSR2 == sig)
		c &= ~(0x80 >> bit);
	bit++;
	if (CHAR_BIT == bit)
	{
		bit = 0;
		if ('\0' == c)
		{
			write(1, "\n", 1);
			ft_kill(client, SIGUSR2);
			c = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	ft_kill(client, SIGUSR1);
}

int	main(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		write(1, "Usage: ./server\n", 16);
		return (EXIT_FAILURE);
	}
	ft_printf("Server PID: %d\n", getpid());
	ft_signal(SIGUSR1, handler, true);
	ft_signal(SIGUSR2, handler, true);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
