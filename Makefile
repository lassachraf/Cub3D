# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 17:38:15 by alassiqu          #+#    #+#              #
#    Updated: 2024/08/14 19:32:18 by alassiqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3D

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -I$(HOME)/local/include

MFLAGS		:=	-L $(HOME)/local/lib -lmlx -lXext -lX11 -lm
RM			:=	rm -f

HEADER		:=	cub3D.h

SRCS		:=	cub3D.c

OBJS		:=	$(SRCS:.c=.o)

MLX			:=	libraries/mlx/libmlx_Linux.a -lXext -lX11 -lm
LIBFT		:=	libraries/libft/libft.a

all:	$(NAME)

$(LIBS)	:
	@make -C libraries/libft
	@cd libraries/mlx && ./configure && make

# Compile source files
%.o: $(SRCS) $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJS) $(LIBS) $(HEADER)
	@$(CC) $(CFLAGS) $(MFLAGS) $(OBJS $(LIBS)) -I $(HEADER) -o $(NAME)

clean:
	@make -C libraries/libft clean
	@make -C libraries/mlx clean
	@$(RM) $(OBJS)

fclean:	clean
	@make -C libraries/libft fclean
	@make -C libraries/mlx fclean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	clean