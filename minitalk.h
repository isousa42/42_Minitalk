#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_info
{
	int				index;
	unsigned char	c;
	char			str[4096];
	int				flag;
	int				client;
}				t_info;

void	conv_char(unsigned char c, int pid);
void	take_sig1(int sig_num);
void	receive_mes(t_info *g_info);
void	conv_char_b(unsigned char c, int pid);
void	receive(int sig_num);
void	conv_this(char *str, char *str_pid, int pid);
void	take_sig1_b(int sig_num);
void	init(t_info *g_info);
void	send_signal(t_info *g_info);
void	choose(t_info *g_info);

#endif
