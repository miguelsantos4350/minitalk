#include "minitalk.h"

/**
 * handler - Processes incoming signals to reconstruct characters
 * @sig: Signal type (SIGUSR1 or SIGUSR2)
 * @info: Signal information containing sender's PID
 * @more_info: Additional context (unused)
 * Note: Uses static variables to maintain state between signal calls
 */
static void	handler(int sig, siginfo_t *info, void *more_info)
{
	static char		c = 0;
	static int		bit = 0;
	static pid_t	client = 0;


	/* Store client PID only once per connection */
	if (info->si_pid) 
		client = info->si_pid;

	/* Build character bit by bit (MSB first) */
	if (SIGUSR1 == sig)
		c |= (0b10000000 >> bit);
	else if (SIGUSR2 == sig)
		c &= ~(0x80 >> bit);
	bit++;

	/* Process complete character */
	if (CHAR_BIT == bit)
	{
		bit = 0;
		if ('\0' == c)
		{
			write(1, "\n", 1);
			Kill(client, SIGUSR2);
			c = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	Kill(client, SIGUSR1);
}

int	main(int argc, char **argv)
{

	if (argc != 1)
	{
		fputs("Usage: ./server\n", stderr);
		return (EXIT_FAILURE);
	}
	
	printf("Server PID: %d\n", getpid());

	/* Set up signal handlers with siginfo enabled */
	Signal(SIGUSR1, handler, true);
	Signal(SIGUSR2, handler, true);

	while (1337)
		pause();
		
	return (EXIT_SUCCESS);
}