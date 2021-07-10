#include "minitalk.h"

t_info	g_info;

void	take_sig1_b(int sig_num)
{
	unsigned char	bit;

	bit = 0b10000000;
	if (sig_num == SIGUSR2)
		g_info.index++;
	if (sig_num == SIGUSR1)
	{
		bit = bit >> g_info.index;
		g_info.c = g_info.c | bit;
		g_info.index++;
	}
}

void	init(t_info *g_info)
{
	pid_t	pid;
	int		i;

	g_info->index = 0;
	g_info->c = 0;
	g_info->flag = 0;
	g_info->client = 0;
	i = 0;
	while (i < 4096)
	{
		g_info->str[i] = 0;
		i++;
	}
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
}

void	send_signal(t_info *g_info)
{
	ft_putstr_fd(g_info->str, 1);
	ft_putchar_fd('\n', 1);
	kill(g_info->client, SIGUSR1);
	g_info->flag = 0;
}

void	choose(t_info *g_info)
{
	if (g_info->flag == 0)
	{
		g_info->client = ft_atoi(g_info->str);
		g_info->flag = 1;
	}
	else
		send_signal(g_info);
	ft_bzero(g_info->str, 4096);
}

int	main(void)
{
	int	i;

	init(&g_info);
	signal(SIGUSR1, take_sig1_b);
	signal(SIGUSR2, take_sig1_b);
	while (1)
	{
		pause();
		if (g_info.index == 8)
		{
			i = 0;
			while (g_info.str[i] != 0)
				i++;
			g_info.str[i] = g_info.c;
			if (g_info.c == '\0')
				choose(&g_info);
			g_info.index = 0;
			g_info.c = 0;
		}
	}
	return (0);
}
