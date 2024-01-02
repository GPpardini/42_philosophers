# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 14:05:24 by gpardini          #+#    #+#              #
#    Updated: 2023/11/22 12:39:39 by gpardini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread -g -fsanitize=thread

SRCS    =	SRC/main.c 				\
			SRC/actions.c			\
			SRC/start.c				\
			SRC/monitor.c			\
			SRC/utils.c				\

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
