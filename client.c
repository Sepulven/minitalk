#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static void	message(int sig)
{
	write(1,"Message sent!\n", 15);
}

static void wait(int pid)
{
	int i;

	i = 0;
        while (i++ < 8)
        {
                kill(pid, SIGUSR1);
                usleep(500);
        }
}

int	main(int argc,  char *argv[])
{
	int	pid;
	int	i;
	int	j;

	i = 0;
	signal(SIGUSR1, message);
	pid = atoi(argv[1]);
	while (argv[2][i])
	{
		j = 8;
		while (--j >= 0)
		{
			if (((argv[2][i] >> j) & 1) == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(800);
		}
		i++;
	}
	wait(pid);
	return (0);
}

