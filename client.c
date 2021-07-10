#include "minitalk.h"

void	conv_char(unsigned char c, int pid)
{
	unsigned char	bit;

	bit = 0b10000000;
	while (bit != 0)
	{
		if ((bit & c))
		{
			kill(pid, SIGUSR1);
		}
		else
			kill(pid, SIGUSR2);
		bit = bit >> 1;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;
	int		i;

	if (argc != 3)
		exit(0);
	str = ft_strdup(argv[2]);
	i = 0;
	pid = 0;
	while (argv[1][i])
	{
		pid = (pid * 10) + argv[1][i] - '0';
		i++;
	}
	while (*str)
	{
		conv_char(*str, pid);
		str++;
	}
	conv_char(0, pid);
	return (0);
}
