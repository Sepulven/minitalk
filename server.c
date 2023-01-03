/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:16:22 by asepulve          #+#    #+#             */
/*   Updated: 2023/01/03 17:37:20 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "./libft/libft.h"

char	*g_str;
int		g_len;

static int		sethandler(void (*handler)(int, siginfo_t *, void *));
static void		setmessage(int signal, siginfo_t *si, void *data);
static void		createstring(int signal, siginfo_t *si, void *data);

void	printbits(char var)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((var >> i--) & 1) == 0)
			write(1, "0", 1);
		else
			write(1, "1", 1);
	}
	write(1, "\n", 1);
	return ;
}


void	createstring(int signal, siginfo_t *si, void *data)
{
	static int	j;
	static int	len;

	(void)data;
	(void)si;

	if (signal == SIGUSR1)
		len = len & ~(1 << (31 - j++));
	if (signal == SIGUSR2)
		len = 1 << (31 - j++) | len;
	if (j == 32)
	{
		j = 0;
		g_str = (char *)malloc((sizeof(char) * len) + 1);
		g_len = len;
		if (!g_str)
			exit(EXIT_FAILURE);
		sethandler(setmessage);
	}
	kill(si->si_pid, SIGUSR1);
	return ;
}

void	setmessage(int signal, siginfo_t *si, void *data)
{
	static int	j;
	static int	i;

	(void)si;
	(void)data;
	if (signal == SIGUSR1)
		g_str[i] = g_str[i] & ~(1 << (7 - j++));
	if (signal == SIGUSR2)
		g_str[i] = 1 << (7 - j++) | g_str[i];
	if (j == 8)
	{
		j = 0;
		i++;
	}
	if (i == g_len)
	{
		i = 0;
		write(1, g_str, g_len);
		kill(si->si_pid, SIGUSR2);
		free(g_str);
		sethandler(createstring);
	}
	else
		kill(si->si_pid, SIGUSR1);
}


static int	sethandler(void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	return (1);
}

int	main(void)
{
	sethandler(createstring);
	ft_putstr_fd("PID:	", 1);
	ft_putstr_fd(ft_itoa(getpid()), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
}
