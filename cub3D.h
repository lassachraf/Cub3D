/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:43:29 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/16 14:37:17 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libraries/mlx/mlx.h"
# include "libraries/libft/libft.h"
# include "get-next-line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define RED	"\033[1;31m"	// for errors !
# define RESET	"\033[0m"		// color reset !

// for compilation until now : 
// gcc cub3D.c -I /usr/local/include -L /usr/local/lib -lmlx -lXext -lX11 -lm -o cub3D

typedef struct s_map
{
	int			fd;
	int			ceil;
	char		*east;
	char		*west;
	char		**map;
	char		**file;
	char		*north;
	int			floor;
	char		*south;
	int			n;
	int			s;
	int			e;
	int			w;
}				t_map;

typedef struct	s_player
{
	
}				t_player;

typedef	struct	s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

typedef struct s_cub3D
{
	t_gc		*gc;
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
}				t_cub3D;

/* get_next_line */ 

char	*get_next_line(int fd);

/* Memory */

// Function that add back an address to the garbage collector.
void	small_add_back(t_gc **gc, t_gc *new_node);

// Function that add an address to the garbage collector.
void	gc_add(t_cub3D *game, void *ptr);

// A custome malloc to alloc and add the address to the garbage collector directly.
void	*ft_malloc(t_cub3D *game, size_t size);

// Function that add a double pointer to the garbage collector.
void	add_split_to_gc(t_cub3D *game, char **split);

// Function that free the garbage collector.
void	gc_free_all(t_cub3D *game);

/* Printing */

void	ft_errors(t_cub3D *game, char *msg);

#endif