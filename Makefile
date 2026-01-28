# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 17:33:26 by losypenk          #+#    #+#              #
#    Updated: 2026/01/26 11:48:46 by jinzhang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC := src/main.c \
		src/parsing/parsing.c \
		src/parsing/parse_ambient.c \
		src/parsing/parse_camera.c \
		src/parsing/parse_light.c \
		src/parsing/parse_object.c \
		src/parsing/parse_error.c \
		src/parsing/parse_utils.c \
		src/utils/string_utils.c \
		src/utils/ft_split.c \
		src/utils/number_utils.c \
		get_next_line/src/get_next_line.c \
		get_next_line/src/get_next_line_utils.c

OBJ := $(SRC:%.c=obj/%.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -I get_next_line/include -Isrc -MMD -MP

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

obj:
	mkdir -p obj
	mkdir -p obj/src/
	mkdir -p obj/src/parsing/
	mkdir -p obj/src/utils/
	mkdir -p obj/get_next_line/src/

obj/%.o: %.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean
	+$(MAKE) all

-include $(OBJ:.o=.d)
