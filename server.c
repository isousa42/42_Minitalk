#include "minitalk.h"

t_info	g_info;

void	take_sig1(int sig_num)
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

void	receive_mes(t_info *g_info)
{
	int	i;

	pause();
	if (g_info->index == 8)
	{
		i = 0;
		while (g_info->str[i] != 0)
			i++;
		g_info->str[i] = g_info->c;
		if (g_info->c == '\0')
		{
			ft_putstr_fd(g_info->str, 1);
			ft_putchar_fd('\n', 1);
			i = 0;
			while (i < 4096)
			{
				g_info->str[i] = 0;
				i++;
			}
		}
		g_info->index = 0;
		g_info->c = 0;
	}
}

int	main(void)
{
	pid_t	pid;
	int		i;

	g_info.index = 0;
	g_info.c = 0;
	i = 0;
	while (i < 4096)
	{
		g_info.str[i] = 0;
		i++;
	}
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, take_sig1);
	signal(SIGUSR2, take_sig1);
	while (1)
		receive_mes(&g_info);
	return (0);
}
