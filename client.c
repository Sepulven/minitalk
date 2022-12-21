#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int	main(int argc,  char *argv[])
{
	int	pid;
	int	i;
	int	j;
	int	bit;

	clock_t start_t,  end_t;
	double	total_t;

	start_t = clock();
	i = 0;
	printf("PID: %s\n", argv[1]);
	printf("My PID: %d\n", getpid());
	pid = atoi(argv[1]);
	while (argv[2][i])
	{
		j = 7;
		while (j >= 0)
		{
			bit = (argv[2][i] >> j) & 1;
			if (bit == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j--;
			usleep(700);
		}
		i++;
	}
	end_t = clock();
	printf("END1!\n");
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
      	printf("Total time taken by CPU: %f \n", total_t);	
	return (0);
}

