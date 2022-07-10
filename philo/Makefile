# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 18:38:53 by cyelena           #+#    #+#              #
#    Updated: 2022/07/10 15:07:37 by cyelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

INC		= includes/philosophers.h

FILES		= philosophers.c utils.c active.c init.c time.c
SRCS_DIR		= srcs/

SRCS		= $(addprefix $(SRCS_DIR), $(FILES))

CC			= gcc

FLAGS		= -Wall -Werror -Wextra -pthread #-g -fsanitize=thread

OBJS 		= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS) $(INC)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

%.o: %.c $(INC) Makefile
	$(CC) $(FLAGS) -c $< -o $@
		
clean:
		rm -rf $(OBJS)
		
fclean: clean
		rm -rf $(NAME)
		
re: fclean all

.PHONY: all clean fclean re	
