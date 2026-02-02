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

SRC := \
src/app_destroy.c \
src/app_hook_add.c \
src/app_init.c \
src/app_run.c \
src/cam.c \
src/dbg_wrld.c \
src/err.c \
src/main.c \
src/plane_intersection.c \
src/sphere_intersection.c \
src/utils2.c \
src/utils3.c \
src/utils.c \
src/v3-0.c \
src/v3-1.c \
src/v3-2.c \
src/v3-3.c

OBJ := $(SRC:src/%.c=obj/%.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -Isrc -Iminilibx-linux -MMD -MP $(CF)
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

obj/%.o: src/%.c minilibx-linux | obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./minilibx-linux clean
	$(RM) libmlx.a
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean
	+$(MAKE) all

-include $(OBJ:.o=.d)
