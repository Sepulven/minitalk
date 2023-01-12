/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:16:22 by asepulve          #+#    #+#             */
/*   Updated: 2023/01/05 16:15:36 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "./libft/libft.h"

struct s_msg
{
	char	*str;	
	int		len;
	int		pid;
	int		i;
};
typedef struct s_msg	t_msg;
t_msg					g_msg;

static int		sethandler(void (*handler)(int, siginfo_t *, void *));
static void		setmessage(int signal, siginfo_t *si, void *data);
static void		createstring(int signal, siginfo_t *si, void *data);

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
		g_msg.str = (char *)malloc((sizeof(char) * len) + 1);
		g_msg.len = len;
		g_msg.pid = si->si_pid;
		if (!g_msg.str)
			exit(EXIT_FAILURE);
		sethandler(setmessage);
	}
	else
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
		g_msg.str[i] = g_msg.str[i] & ~(1 << (7 - j++));
	if (signal == SIGUSR2)
		g_msg.str[i] = 1 << (7 - j++) | g_msg.str[i];
	if (j == 8)
	{
		j = 0;
		i++;
	}
	if (i == g_msg.len)
	{
		i = 0;
		write(1, g_msg.str, g_msg.len);
		kill(si->si_pid, SIGUSR2);
		free(g_msg.str);
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
