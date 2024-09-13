# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 11:36:40 by alassiqu          #+#    #+#              #
#    Updated: 2024/09/07 10:12:33 by alassiqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3D

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -fsanitize=address -g3

MFLAGS		:=	-I /usr/local/include -L /usr/local/lib -lmlx -lXext -lX11 -lm
RM			:=	rm -f

HEADER		:=	cub3D.h

GNL			:=	get-next-line/get_next_line_utils.c		\
				get-next-line/get_next_line.c

MEMORY		:=	memory/memory.c							\
				memory/mem.c

PARSING		:=	parsing/colors_textures_utils.c			\
				parsing/map_utils.c						\
				parsing/parsing_utils.c					\
				parsing/parsing.c						\
				parsing/player_utils.c

RENDERING	:=	rendering/rays_things.c							\
				rendering/render_map.c							\
				rendering/render_utils.c

PRINTING	:=	printing.c

SRCS		:=	$(GNL)									\
				$(MAP)									\
				$(MEMORY)								\
				$(PARSING)								\
				$(RENDERING)							\
				$(PRINTING)								\
				cub3D.c

OBJS		:=	$(SRCS:.c=.o)

LIBFT		:=	libraries/libft/libft.a
MLX			:=	libraries/mlx/libmlx_Linux.a

LIBS		:=	$(LIBFT) $(MLX)

# Colors
GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
RESET		:=	\033[0m
YELLOW		:=	\033[1;33m
UCYAN		:=	\033[0;34m

all:	$(NAME)

ASCII_ART	:=	"\
\n\
\n\
 ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \n\
██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n\
██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n\
██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n\
╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n\
 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \n\
\n\
"

$(LIBFT):
	@echo "$(RED)** Building Libft. **$(YELLOW)"
	@make -C libraries/libft
	@echo "$(RED)** Libft builded succesfully. **$(RESET)"

$(MLX):
	@echo "$(RED)** Building MLX. **$(GREEN)"
	@cd libraries/mlx && ./configure && make
	@echo "$(RED)** MLX builded succesfully. **$(RESET)"

$(NAME)	:	$(LIBFT) $(MLX) $(OBJS)
	@echo "$(RED)** Linking. **$(YELLOW)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MFLAGS) -o $(NAME)
	@printf "$(UCYAN)"
	@printf $(ASCII_ART)
	@echo "$(RED)** Cub3D is waiting ! **$(RESET)"

clean:
	@echo "$(RED)** Cleaning Object Files. **$(YELLOW)"
	@make -C libraries/libft clean
	@$(RM) $(OBJS)

fclean:	clean
	@echo "$(RED)** Cleaning. **$(YELLOW)"
	@make -C libraries/libft fclean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	clean fclean all re $(LIBFT) $(MLX)