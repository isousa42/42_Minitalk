#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

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

// char *str_binary(char *str)
// {
//     int size;
//     char *binary;
//     char *copy;

//     if (!str)
//         return (NULL);
//     size = ft_strlen(str);
//     binary = malloc(size * 8 + 1);
//     if (!binary)
//         return (NULL);
//     if (size == 0)
//     {
//         binary = NULL;
//         return (binary);
//     }
//     copy = str;
//     int i = 0;
//     int j;
//     int x = 0;
//     while (copy[i] != 0)
//     {
//         j = 8;
//         while (j > 0)
//         {
//             if ((copy[i] & 1 << j) == 0)
//                 binary[x] = '0';
//             else
//                 binary[x] = '1';
//             x++;
//             j--;
//         }
//         i++;
//     }
//     binary[x] = '\0';
//     return(binary);
// }

void conv_char(unsigned char c, int pid)
{
    unsigned char bit = 0b10000000;
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

int main(int argc, char **argv)
{
    int pid;
    char *str = argv[2];
    char *temp;
    char *binary;

    int i = 0;
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
    //i = 2;
    // str = ft_strdup("");
    // while (i < argc)
    // {
    //     temp = ft_strdup(argv[i]);
    //     if (i != (argc - 1))
    //         temp[ft_strlen(argv[i])] = ' ';
    //         temp[ft_strlen(argv[i]) + 1] = '\0';
    //     str = ft_strjoin(str, temp);
    //     free(temp);
    //     i++;
    // }
    // binary = str_binary(str);
    // i = 0;
    // while (binary[i])
    // {
    //     if (binary[i] == '1')
    //     {
    //         kill(pid, SIGUSR1);
    //         sleep(1);
    //     }
    //     else if (binary[i] == '0')
    //     {
    //         kill(pid, SIGUSR2);
    //         sleep(1);
    //     }
    //     i++;
    // }
    return (0);
}