# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aerrajiy <aerrajiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 20:02:25 by aerrajiy          #+#    #+#              #
#    Updated: 2023/02/06 15:50:02 by aerrajiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread -g

SRC = philo_main.c \
	  philo_tools.c \
	  philo_pars.c \
	  philo_time.c \
	  philo_init.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)
bonus:$(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
