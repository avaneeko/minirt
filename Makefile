# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 17:33:26 by losypenk          #+#    #+#              #
#    Updated: 2026/01/13 18:07:18 by jinzhang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRC := src/main.c

OBJ := $(SRC:src/%.c=obj/%.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -Isrc -MMD -MP

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

obj:
	mkdir -p obj
	mkdir -p obj/Builtins/
	mkdir -p obj/Execution/
	mkdir -p obj/Signals/

0
obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean
	+$(MAKE) all

-include $(OBJ:.o=.d)
