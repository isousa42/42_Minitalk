#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_info
{
    int index;
    unsigned char c;
    char str[4096];
}               t_info;

t_info g_info;

int ft_strlen(char *str)
{
    int counter;

    counter = 0;
    while (str[counter])
        counter++;
    return (counter);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	if ((dest = malloc(ft_strlen(src) * sizeof(char) + 1)) == NULL)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!new)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

void    take_sig1(int sig_num)
{
    unsigned char bit = 0b10000000;

    if (sig_num == SIGUSR2)
    {
        printf("0\n");

        g_info.index++;
    }
    if (sig_num == SIGUSR1)
    {
        printf("1\n");

        bit = bit >> g_info.index;
        g_info.c = g_info.c | bit;
        g_info.index++;
    }
}

int main()
{
    pid_t pid;
    char *display;

    g_info.index = 0;
    g_info.c = 0;
    int i = 0;
    while (i < 4096)
    {
        g_info.str[i] = 0;
        i++;
    }
    pid = getpid();
    printf("%d\n", pid);

    if(signal(SIGUSR1, take_sig1) == SIG_ERR)
        printf("IMPOSSIBLE\n");
    else if(signal(SIGUSR2, take_sig1) == SIG_ERR)
        printf("IMPOSSIBLE\n");
    while(1)
    {
        pause();

        if (g_info.index == 8)
        {
            int i = 0;
            while (g_info.str[i] != 0)
                i++;
            g_info.str[i] = g_info.c;
            if (g_info.c == '\0')
            {
                printf("%s\n", g_info.str);
                i = 0;
                while (i < 4096)
                {
                    g_info.str[i] = 0;
                    i++;
                }
            }
            g_info.index = 0;
            g_info.c = 0;
        }
    }
    return (0);
}