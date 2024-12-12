/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos <msantos@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:23:15 by msantos           #+#    #+#             */
/*   Updated: 2024/12/12 16:01:24 by msantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_signal(int sig, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	if (use_siginfo)
	{
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(sig, &sa, NULL) < 0)
	{
		write(1, "ERROR", 5);
		exit(EXIT_FAILURE);
	}
}

void	ft_kill(pid_t pid, int signum)
{
	if (kill(pid, signum) < 0)
	{
		write(1, "INVALID PID", 11);
		exit(EXIT_FAILURE);
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		flag;
	long	result;

	i = 0;
	flag = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	return (result * flag);
}
