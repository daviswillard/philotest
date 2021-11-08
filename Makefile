# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwillard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 20:05:03 by dwillard          #+#    #+#              #
#    Updated: 2021/11/08 20:05:05 by dwillard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror -MMD

SRC_DIR = sources/

SRCS = $(SRC_DIR)main.c $(SRC_DIR)init.c $(SRC_DIR)threads.c \
		$(SRC_DIR)utils.c $(SRC_DIR)watch.c

OBJS = ${SRCS:.c=.o}
DEP = ${SRCS:.c=.d}

all: $(NAME)

.c.o:
	gcc $(FLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS) $(DEP)

fclean: clean
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re
-include	$(OBJS:.o=.d)