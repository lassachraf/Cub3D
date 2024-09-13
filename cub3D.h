/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:58:06 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/13 20:40:21 by alassiqu         ###   ########.fr       */
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
# include <math.h>

# define	PI			3.14159265358979323846
# define	RED			"\033[1;31m"	// for errors !
# define	RESET		"\033[0m"		// color reset !
# define	TILE_SIZE	32

// # define	WALL_STRIP	4

# define	ESC_KEY		65307

# define	LEFT_ARROW	65361
# define	UP_ARROW	65362
# define	RIGHT_ARROW	65363
# define	DOWN_ARROW	65364

# define	A_KEY		97
# define	W_KEY		119
# define	D_KEY		100
# define	S_KEY		115

typedef struct s_map
{
	int			n;
	int			s;
	int			e;
	int			w;
	int			f;
	int			c;
	int			fd;
	int			ceil;
	int			start;
	int			floor;
	int			width;
	char		*east;
	char		*west;
	char		**map;
	int			height;
	char		**file;
	char		*north;
	char		*south;
	int			counter;
}				t_map;

typedef struct	s_player
{
	float		x;
	float		y;
	int			count;
	long		radius;
	float		movespeed;
	float		rotationspeed;
	int			turndirection;
	int			walkdirection;
	float		rotationangle;
}				t_player;

typedef struct	s_ray
{
    float   	distance;
	float		ray_angle;
	int			facing_up;
    float   	wall_hit_x;
    float   	wall_hit_y;
	int			facing_down;
	int			facing_left;
	int			facing_right;
}           	t_ray;

typedef	struct s_rays
{
	t_ray		*lst_of_rays;
}				t_rays;


typedef	struct	s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

typedef struct s_cub3D
{
	t_gc		*gc;
	int			bpp;
	int			end;
	int			szl;
	int			wov;
	int			hov;
	void		*mlx;
	void		*win;
	void		*img;
	t_map		*map;
	char		*addr;
	int			deltax;
	int			deltay;
	float		fov_ang;
	float		nb_rays;
	float		df_rays;
	t_rays		*rays;
	t_player	*player;
}				t_cub3D;

/* get_next_line */

char	*get_next_line(int fd);

/* parsing functions */

// Function that check and get textures, ceil and floor colors. 
int		textures_and_colors_element(t_cub3D *game, t_map *map, char **line);

// Function that parse every line of the map file.
void	parse_line(t_cub3D *game, t_map *map, char **line);

// Function that checks the validity of the map.
void	check_surrounded(t_cub3D *game, t_map *maps);

// Function that check if c is a player.
int		is_it_player(char c);

//
void	adjust_rotation(t_player *player, char **map);

// Function that allocate and fill map.
void	alloc_and_fill_map(t_cub3D *game, t_map *map);

//
char	*add_and_strdup(t_cub3D *game, void *pointer);

// Function that checks the file extension.
void	ft_extension(t_cub3D *game, char *mapfile, char *ext);

// Function that check if c is a valid map element.
int		is_map_element(char c);

//
int		basic_checks(t_cub3D *game, t_map *map, char **line);

// Main parsing funtion.
t_cub3D	*parsing(t_cub3D *game, char *av);

/* memory functions */

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

// Function that add a pointer to the gc using a flag.
void	add_to_gc(t_cub3D *game, t_map *map, int flag);

// Function that free a double pointer.
void	free_double(char **s);

// Function that join two words and free the first one.
char	*free_and_join(char *line, char **lines);

// Function that clean cub3D.
void	clean_cub3D(t_cub3D *game);

/* printing functions */

// Function that prints a char double pointer. 
void	print_double(char **dbl);

// Main function to print error.
void	ft_errors(t_cub3D *game, char *msg);

// Function that print map info.
void	print_map_info(t_map *map);

// Function that print player info.
void	print_player_info(t_player *player);

/* rendering functions */

int		ft_exit(t_cub3D *game);

int		ft_moving(int keycode, t_cub3D *game);
int 	is_walkable(t_cub3D *game, float new_x, float new_y);
void	my_mlx_pixel_put(t_cub3D *game, float x, float y, int color);
void    render_map(t_cub3D *game);
void    render_map_2(t_cub3D *game);
void    render_circle(t_cub3D *game, int cx, int cy, int radius, int color);
void    render_square(t_cub3D *game, float x, float y, int color);
void    render_line(t_cub3D *game, int cx, int cy, int length, int color);

float	normalize_angle(float angle);
int		get_y_index(float y);
int		get_x_index(t_cub3D *game, float y, float yint, int id);
float	*find_walls(t_cub3D *game, float *x, float *y, int id);
void	cast(t_cub3D *game, int id);
void	render_ray(t_cub3D *game, float ray_angle, int color);
void 	render_rays(t_cub3D *game);
int		facingdown(t_cub3D *game, int id);
int		facingright(t_cub3D *game, int id);
void	castAllRays(t_cub3D *game);

#endif