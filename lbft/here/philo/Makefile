# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 20:02:25 by aerrajiy          #+#    #+#              #
#    Updated: 2023/02/05 21:41:59 by aerrajiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread -g

SRC = ./source/_philo.c \
	  ./source/_philo_life.c \
	  ./source/_philo_mutex.c \
	  ./source/_philo_pars.c \
	  ./source/_philo_time.c \
	  ./source/philo_tools/ft_atoi.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
