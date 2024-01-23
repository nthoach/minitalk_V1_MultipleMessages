/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:19:41 by honguyen          #+#    #+#             */
/*   Updated: 2024/01/22 16:51:45 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
/* if success with '\0' send SIGUSR1
else print char and send SIGUSR2 */

void	print_sendback(int signo, siginfo_t *info, void *context)
{
	static int	bit;
	static int	character;

	(void)context;
	if (signo == SIGUSR1)
		character += 1 << (7 - bit);
	bit++;
	if (bit == 8)
	{
		if (character == '\0')
		{
			if (kill(info->si_pid, SIGUSR1) == -1)
				ft_printf("Sending SIGUSR1 Got Error \n");
		}
		if (character != '\0')
		{
			ft_printf("%c", character);
			kill(info->si_pid, SIGUSR2);
		}
		bit = 0;
		character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server's Process Indentifier (PID): %d\n", getpid());
	sa.sa_sigaction = &print_sendback;
	sa.sa_flags = SA_SIGINFO;
	while (1)
	{
		if (sigaction(SIGUSR1, &sa, NULL) == -1)
		{
			ft_printf("Getting error when setting up signal: SIGUSR1\n");
			return (1);
		}
		if (sigaction(SIGUSR2, &sa, NULL) == -1)
		{
			ft_printf("Getting error when setting up signal: SIGUSR2\n");
			return (2);
		}
		pause();
	}
	return (0);
}
