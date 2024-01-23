/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:23:34 by honguyen          #+#    #+#             */
/*   Updated: 2024/01/22 16:56:41 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/*send a character by sending bit by bit starting from most-valued bit to 
the least one, SIGUSR1 will send 1 and SIGUSR2 will sent 0, error message
when signal cannot send, 50 us for delay between bit sending*/

void	send_char(int server_pid, char ch)
{
	int	bit;
	int	one;

	bit = 0;
	one = 0x80;
	while (bit++ < 8)
	{
		if (ch & one)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				ft_printf("Error on Sending SIGUSR1.\n");
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				ft_printf("Error on Sending SIGUSR2.\n");
		}
		one >>= 1;
		usleep(100);
	}
}

/* send the whole string char by char, send newline and zero
chars to mark the end */

void	send_string(int server_pid, char *msg, int stop)
{
	while (*msg)
	{
		send_char(server_pid, *msg);
		msg++;
	}
	if (!*msg)
	{
		send_char(server_pid, ' ');
		if (stop)
		{
			send_char(server_pid, '\n');
			send_char(server_pid, '\0');
		}

	}
}

/*receiving back signal from the server
if SIGUSR1 means server recevieed and prince out the result
if not SIGUSR1 (SIGUSR2) mean counting  the bytes
the variabe "bt_ct" is set at zero with the main program, counting up at every
time the server send SIGUSR2 as it printing a char - 1 byte
total bytes sent is by_ct - 1 because we exculude the additioanl '\n' */

void	recv_print(int sign)
{
	static int	by_ct;

	if (sign == SIGUSR1)
	{
		ft_printf("Message received.\n%d bytes.\n", (by_ct - 1));
		exit(0);
	}
	else if (sign == SIGUSR2)
		by_ct++;
}

/* register the handler fuction to both interupt signal SIGUSR1 and SIGUSR2*/

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_pid;
	int					i;
	int					stop;

	stop = 0;
	i = 2;
	if (argc >= 3)
	{
		sa.sa_handler = &recv_print;
		sa.sa_flags = SA_SIGINFO;
		server_pid = ft_atoi(argv[1]);
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		while (i < argc)
		{
			if (i == argc - 1)
				stop = 1;
			send_string(server_pid, argv[i], stop);
			i++;
		}

		while (1)
			pause();
	}
	else
	{
		ft_printf("Number of arguments should be more than 2.\n");
		ft_printf("e.g.: ./client [PID] [message]\n");
		return (1);
	}
	return (0);
}
