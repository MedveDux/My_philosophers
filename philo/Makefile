# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 18:38:53 by cyelena           #+#    #+#              #
#    Updated: 2022/07/08 18:53:50 by cyelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

INC		= includes/philosophers.h

FILES		= philosophers.c utils.c
SRCS_DIR		= srcs/

SRCS		= $(addprefix $(SRCS_DIR), $(FILES))

CC			= gcc

FLAG		= -Wall -Werror -Wextra -pthread
FLAGS		= #-g -fsanitize=address
# -g -fsanitize=address
OBJS 		= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS) $(INC)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)
#  $(CC) $(SRCS) -o $(NAME)

%.o: %.c $(INC) Makefile
	$(CC) $(FLAGS) -c $< -o $@
# $(CC) -c $< -o $@
		
clean:
		rm -rf $(OBJS)
		
fclean:
		rm -rf $(NAME)
		
re: fclean all

.PHONY: all clean fclean re	
