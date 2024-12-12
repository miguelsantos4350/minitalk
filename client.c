#include "minitalk.h"

/* Global flag for synchronization between client and server */
volatile sig_atomic_t	g_server = BUSY;

/**
 * end_handler - Handles server's completion signal
 * @sig: Signal number (unused)
 */
static void	end_handler(int sig)
{
	write(1 ,"Message recieved\n", 17);
	exit(EXIT_SUCCESS);
}

/**
 * ack_handler - Handles server's acknowledgment signals
 * @sig: Signal number (unused)
 */
static void	ack_handler(int sig)
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

		/* Send SIGUSR1 for 1, SIGUSR2 for 0 */
		if (c & (0x80 >> bit))
			Kill(server, SIGUSR1);
		else
			Kill(server, SIGUSR2);
		bit++;

		/* Wait for server acknowledgment */
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
        write(1 ,"Usage: ./client <server> \"message\"\n", 36);
		return (EXIT_FAILURE);
	}
	server = atoi(argv[1]);
	message = argv[2];

	/* Set up signal handlers without siginfo */
	Signal(SIGUSR1, ack_handler, false);
	Signal(SIGUSR2, end_handler, false);

	i = 0;
	while (message[i])
		send_char(message[i++], server);
	send_char('\0', server);

	return (EXIT_SUCCESS);
}