# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 17:38:15 by alassiqu          #+#    #+#              #
#    Updated: 2024/08/29 16:34:35 by alassiqu         ###   ########.fr        #
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

PARSING		:=	parsing/colors.c						\
				parsing/file_parsing.c					\
				parsing/map_element.c					\
				parsing/map_parsing.c					\
				parsing/map_utils.c

MAP			:=	map/rendering.c							\
				map/utils.c

SRCS		:=	$(GNL)									\
				$(MAP)									\
				$(MEMORY)								\
				$(PARSING)								\
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