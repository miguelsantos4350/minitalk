/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos <msantos@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:22:59 by msantos           #+#    #+#             */
/*   Updated: 2024/12/12 15:41:44 by msantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>

# define BUSY	0
# define READY	1

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

void	ft_signal(int sig, void *handler, bool use_siginfo);
void	ft_kill(pid_t pid, int signum);
int		ft_atoi(const char *str);
int		ft_printf(const char *type, ...);

#endif
