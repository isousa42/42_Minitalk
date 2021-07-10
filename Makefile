CC	= gcc
FLAGS = -Wall -Wextra -Werror
RM	= rm -f

NAME_C = client
NAME_S = server

SRCS_C = client.c
SRCS_S = server.c
SRCS_C_B = client_bonus.c
SRCS_S_B = server_bonus.c
LIBFT = ./libft/libft.a

OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_S:.c=.o)
OBJS_C_B = $(SRCS_C:.c=.o)
OBJS_S_B = $(SRCS_S:.c=.o)

all: $(NAME_C) $(NAME_S)

$(NAME_C) : 
	$(MAKE) bonus -C libft
	gcc $(SRCS_C) $(FLAGS) $(LIBFT) -o $(NAME_C)

$(NAME_S) : 
	gcc $(SRCS_S) $(FLAGS) $(LIBFT) -o $(NAME_S)

bonus : 
	$(MAKE) bonus -C libft
	gcc $(SRCS_C_B) $(FLAGS) $(LIBFT) -o $(NAME_C)
	gcc $(SRCS_S_B) $(FLAGS) $(LIBFT) -o $(NAME_S)

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJS_C) 
	$(RM) $(OBJS_S) 
	$(RM) $(OBJS_C_B) 
	$(RM) $(OBJS_S_B)


fclean: clean
	 	$(RM) $(NAME_C)
	 	$(RM) $(NAME_S)

re: fclean all

.PHONY:		all clean fclean re 