/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:13:36 by asepulve          #+#    #+#             */
/*   Updated: 2023/01/05 17:41:38 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"

static void	sendmessage(size_t pid, char *msg);
static void	handler(int signal, siginfo_t *si, void *data);
static void	sendlength(int pid, char *str);
static void	error(char *msg);

static void	error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

static void	sendlength(int pid, char *str)
{
	int	len;
	int	j;

	j = 31;
	len = ft_strlen(str);
	while (j >= 0)
	{
		if (((len >> j--) & 1) == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				error("Wrong pid\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error("Wrong pid\n");
		}
		usleep(500);
	}
}

static void	handler(int signal, siginfo_t *si, void *data)
{
	(void)si;
	(void)data;
	if (signal == SIGUSR1)
		return ;
	write(1, "Message sent! 🦞", 19);
	exit(EXIT_SUCCESS);
}

static void	sendmessage(size_t pid, char *msg)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 7;
		while (j >= 0)
		{
			if (((msg[i] >> j--) & 1) == 0)
			{
				if (kill(pid, SIGUSR1) == -1)
					error("Wrong pid\n");
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					error("Wrong pid\n");
			}
			usleep(500);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	act;

	(void)argc;
	if (!argv[2] || !argv[1] ||!isstralnum(argv[1]))
		error("Arguments not valid!");
	pid = ft_atoi(argv[1]);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sendlength(pid, argv[2]);
	sendmessage(pid, argv[2]);
}
