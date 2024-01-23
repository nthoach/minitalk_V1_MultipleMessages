/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:19:59 by honguyen          #+#    #+#             */
/*   Updated: 2024/01/18 17:43:51 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	rec_char_print(int sig)
{
	static int	bit;
	static char	ch;

	if (sig == SIGUSR1)
		ch += 1 << (7 - bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", ch);
		bit = 0;
		ch = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, rec_char_print);
		signal(SIGUSR2, rec_char_print);
	}
	return (0);
}
