/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:13:36 by asepulve          #+#    #+#             */
/*   Updated: 2023/01/03 17:36:12 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"

static int	isstralnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
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
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
	}
}

static void	handler(int signal, siginfo_t *si, void *data)
{
	(void)si;
	(void)data;
	if (signal == SIGUSR1)
		return ;
	write(1, "Message sent successfully! 👩‍🦰", 39);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	int					pid;
	int					i;
	int					j;
	struct sigaction	act;

	(void)argc;
	i = 0;
	if (!argv[2] || !argv[1] ||!isstralnum(argv[1]))
		return (0);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	pid = ft_atoi(argv[1]);
	sendlength(pid, argv[2]);
	while (argv[2][i])
	{
		j = 7;
		while (j >= 0)
		{
			if (((argv[2][i] >> j--) & 1) == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(500);
		}
		i++;
	}
}
