#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	*clientpid()
{
	static int pid;
	return (&pid);
}

void handler(int signal, siginfo_t *si, void *data)
{
	static char	c;
	static int	j;

	if (j == 0)
        {
		j = 8;
		write(1, &c, 1);
	}
	j--;
	if (*clientpid() == 0)
		*clientpid() = si->si_pid;
	if (signal == SIGUSR1)
		c = c & ~(1 << j);
	if (signal == SIGUSR2)
		c = 1 << j | c;
	if (j == 0 && c == 0)
	{
                kill(*clientpid(), SIGUSR1);
		*clientpid() = 0;
	}
}

int	main(void)
{
	struct sigaction act;

	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	printf("PID: %d\n", getpid());
	while(1)
		pause();
}
