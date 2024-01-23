/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:45:15 by damachad          #+#    #+#             */
/*   Updated: 2024/01/22 16:56:39 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*send char each bit, 1 for SIGUSR1 and - for SIGUSR2
send highest-value bit first., each bit send will be delay 50 us
to ensure data transfer without loss*/

void	send_char(char ch, int server_pid)
{
	int				bit;
	unsigned char	one;

	bit = 0;
	one = 0x80;
	while (bit <= 7)
	{
		if (ch & one)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		one >>= 1;
		bit++;
		usleep(100);
	}
}

/*Process and validate number of arguments and send the message to the
send_bits function*/

int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;
	int j;
	int stop;

	stop = 0;
	if (argc >= 3)
	{
		server_pid = ft_atoi(argv[1]);
		j = 2;
		while (j < argc)
		{
			if (j == argc - 1)
				stop = 1;
			i = 0;
			while (argv[j][i] != '\0')
			{
				send_char(argv[j][i], server_pid);
				i++;
			}
			if (stop)
			{
				send_char('\n', server_pid);
				send_char('\0', server_pid);
			}
			else
				send_char(' ', server_pid);
			j++;
		}

	}
	else
	{
		ft_printf("Number of arguments should be 2.\n");
		ft_printf("e.g: ./client [PID no] [message]\n");
		return (1);
	}
	return (0);
}
