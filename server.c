#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int bit;

void handler1()
{
	signal(SIGUSR1, handler1);
	bit = 0;
}

void handler2()
{
	signal(SIGUSR2, handler2);
        bit = 1;
}

int	main(void)
{
	int i, j;
	char c;

	printf("PID: %d\n", getpid());
	signal(SIGUSR1, handler1);
	signal(SIGUSR2, handler2);
	
	j = 7;
	i = 0;
	while(1)
	{
		pause();
		if (bit == 1)
			c = 1 << j | c;
		if (bit == 0)
			c = c & ~(1 << j);
		//printf("%d", bit);
		if (j == 0)
		{
			i = 7;
               // 	while (i >= 0)
		//		printf("%d", (c >> i--) & 1);
		//	printf("\n");
			printf("%c",  c);
			fflush(stdout);
			j = 8;
		}
		j--;
	}
	return (0);
}
