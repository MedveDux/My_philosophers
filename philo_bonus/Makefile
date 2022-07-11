# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 17:25:01 by cyelena           #+#    #+#              #
#    Updated: 2022/07/11 18:53:53 by cyelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers_bonus

INC		= includes/philosophers_bonus.h

FILES		= philosophers_bonus.c  utils.c active.c init.c
SRCS_DIR		= srcs/

SRCS		= $(addprefix $(SRCS_DIR), $(FILES))

CC			= gcc

FLAGS		= -Wall -Werror -Wextra -pthread -g -fsanitize=thread

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