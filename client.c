/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos <msantos@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:22:49 by msantos           #+#    #+#             */
/*   Updated: 2024/12/12 16:08:36 by msantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* Global flag for synchronization between client and server */
volatile sig_atomic_t	g_server = BUSY;

/**
 * end_handler - Handles server's completion signal
 * @sig: Signal number (unused)
 */
static void	end_handler(void)
{
	write(1, "Message recieved\n", 17);
	exit(EXIT_SUCCESS);
}

/**
 * ack_handler - Handles server's acknowledgment signals
 * @sig: Signal number (unused)
 */
static void	ack_handler(void)
{
	g_server = READY;
}

/**
 * send_char - Sends a character bit by bit to server
 * @c: Character to send
 * @server: Server's process ID
 */
static void	send_char(char c, pid_t server)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c & (0x80 >> bit))
			ft_kill(server, SIGUSR1);
		else
			ft_kill(server, SIGUSR2);
		bit++;
		while (BUSY == g_server)
			usleep(42);
		g_server = BUSY;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server;
	char	*message;
	int		i;

	if (argc != 3)
	{
		write (1, "Usage: ./client <server> \"message\"\n", 36);
		return (EXIT_FAILURE);
	}
	server = ft_atoi(argv[1]);
	message = argv[2];
	ft_signal(SIGUSR1, ack_handler, false);
	ft_signal(SIGUSR2, end_handler, false);
	i = 0;
	while (message[i])
		send_char(message[i++], server);
	send_char('\0', server);
	return (EXIT_SUCCESS);
}
