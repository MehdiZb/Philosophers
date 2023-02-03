# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 15:43:37 by mzblah            #+#    #+#              #
#    Updated: 2021/05/30 22:51:14 by mzblah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_PATH = ./srcs/

HEADER = ./includes/

SRCS =	$(SRCS_PATH)philosophers.c			\
		$(SRCS_PATH)philo_utils.c			\
		$(SRCS_PATH)philo_utils_2.c			\
		$(SRCS_PATH)philo_free.c			\
		$(SRCS_PATH)philo_threads.c			\
		$(SRCS_PATH)philo_check_eat_death.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LIBS = -lpthread

CC = cc

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LIBS) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
