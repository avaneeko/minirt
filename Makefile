# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 17:33:26 by losypenk          #+#    #+#              #
#    Updated: 2026/02/01 20:09:15 by jinzhang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC := src/main.c \
		src/parsing/parsing.c \
		src/parsing/parse_ambient.c \
		src/parsing/parse_camera.c \
		src/parsing/parse_light.c \
		src/parsing/parse_sphere.c \
		src/parsing/parse_plane.c \
		src/parsing/parse_cylinder.c \
		src/parsing/parse_error.c \
		src/parsing/parse_utils.c \
		src/utils/string_utils.c \
		src/utils/ft_split.c \
		src/utils/number_utils.c \
		get_next_line/src/get_next_line.c \
		get_next_line/src/get_next_line_utils.c \
		src/app_destroy.c \
		src/app_hook_add.c \
		src/app_init.c \
		src/app_run.c \
		src/cam.c \
		src/dbg_wrld.c \
		src/err.c \
		src/sphere_intersection.c \
		src/utils2.c \
		src/utils3.c \
		src/utils.c \
		src/v3-0.c \
		src/v3-1.c \
		src/v3-2.c \
		src/v3-3.c

OBJ := $(SRC:%.c=obj/%.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -Isrc -Iget_next_line/include -Iminilibx-linux -MMD -MP $(CF)
LDFLAGS := -L. -lm -lmlx -lXext -lX11 $(LDF)

all: $(NAME)

$(NAME): $(OBJ) libmlx.a
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

minilibx-linux:
	git clone --recursive https://github.com/42paris/minilibx-linux

libmlx.a: minilibx-linux
	+$(MAKE) -C ./minilibx-linux
	mv minilibx-linux/libmlx.a ./libmlx.a

obj:
	mkdir -p obj
	mkdir -p obj/src/
	mkdir -p obj/src/parsing/
	mkdir -p obj/src/utils/
	mkdir -p obj/get_next_line/src/

obj/%.o: %.c minilibx-linux | obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(MAKE) -C ./minilibx-linux clean
	$(RM) -f libmlx.a
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean
	+$(MAKE) all

-include $(OBJ:.o=.d)
