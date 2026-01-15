# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 17:33:26 by losypenk          #+#    #+#              #
#    Updated: 2026/01/15 17:54:30 by jinzhang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRC := src/main.c \
		src/parsing/parsing.c \
		src/utils/string_utils.c \

GNL_SRC := get_next_line/src/get_next_line.c get_next_line/src/get_next_line_utils.c \

SRCS := $ $(SRC) $(GNL_SRCS)

OBJ := $(SRCS:src/%.c=obj/%.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -I get_next_line/include -Isrc -MMD -MP

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

obj:
	mkdir -p obj
	mkdir -p obj/parsing/
	mkdir -p obj/utils/

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean
	+$(MAKE) all

-include $(OBJ:.o=.d)
