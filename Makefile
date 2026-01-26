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
src/utils2.c \
src/utils3.c \
src/utils.c \
src/v3-0.c \
src/v3-1.c \
src/v3-2.c \
src/v3-3.c

OBJ := $(SRC:src/%.c=obj/%.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -Isrc -Iminilibx -MMD -MP $(CF)
LDFLAGS := -L. -lm -lmlx -lXext -lX11 $(LDF)

all: $(NAME)

$(NAME): $(OBJ) libmlx.a
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

libmlx.a:
	+$(MAKE) -C ./minilibx
	mv minilibx/libmlx.a ./libmlx.a

obj:
	mkdir -p obj

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./minilibx clean
	$(RM) libmlx.a
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean
	+$(MAKE) all

-include $(OBJ:.o=.d)
