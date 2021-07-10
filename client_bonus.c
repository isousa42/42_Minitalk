#include "minitalk.h"

void	conv_char_b(unsigned char c, int pid)
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

void	receive(int sig_num)
{
	(void)sig_num;
	write(1, "Message Received\n", 17);
	exit(0);
}

void	conv_this(char *str, char *str_pid, int pid)
{
	while (*str_pid)
	{
		conv_char_b(*str_pid, pid);
		str_pid++;
	}
	conv_char_b(0, pid);
	while (*str)
	{
		conv_char_b(*str, pid);
		str++;
	}
	conv_char_b(0, pid);
}

int	main(int argc, char **argv)
{
	int		pid;
	pid_t	pid_client;
	char	*str_pid;
	char	*str;
	int		i;

	signal(SIGUSR1, receive);
	str = ft_strdup(argv[2]);
	pid_client = getpid();
	if (argc != 3)
		exit(0);
	str_pid = ft_itoa(pid_client);
	i = 0;
	pid = 0;
	while (argv[1][i])
	{
		pid = (pid * 10) + argv[1][i] - '0';
		i++;
	}
	conv_this(str, str_pid, pid);
	free(str_pid);
	free(str);
	pause();
	return (0);
}
