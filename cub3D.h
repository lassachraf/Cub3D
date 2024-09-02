/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:43:29 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/31 14:16:01 by alassiqu         ###   ########.fr       */
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
	int			fd;
	int			ceil;
	int			floor;
	int			width;
	int			height;
	char		*east;
	char		*west;
	char		**map;
	char		**file;
	char		*north;
	char		*south;
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
	long		ray_angle;
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


/* Parsing */

/* get_next_line */
char	*get_next_line(int fd);

// Function "ASCII TO INTEGER" customize for colors.
int		ft_atoi_rgb(t_cub3D *game, char **str);

// Function of mlx functions that create a TRGB.
int		create_trgb(int t, int r, int g, int b);

// Main function that create colors. 
int		ft_colors(t_cub3D *game, char *s);

// Function that checks for a specified extension.
void	ft_extension(t_cub3D *game, char *argv, char *ext);

// Function that get file content.
char	**get_file_content(t_cub3D *game, int fd);

// Function that skip white lines.
int		skip_white_lines(char **s, int *i);

// Function that skip leading whitespaces in a line.
void	skip_whitespaces(char *s, int *i);

// Function that get the width and height of the map and check for it first and last element.
int		get_map_info(t_cub3D *game, char **map, int i, int *h);

// Function that alloc and fill the map.
char	**alloc_and_fill_map(t_cub3D *game, char **map_1, int w, int h);

// Function that check if all map element are valid.
void	check_map_element(t_cub3D *game, t_map *map);

// Function that check first element of the line.
void	check_first_element(t_cub3D *game, char **map, int *j, int *k);

// Function that check first element of the line.
int		check_last_element(t_cub3D *game, char *s);

// Function that checks if the map is surrounded bu walls.
void	check_surrounded(t_cub3D *game, char **map, int nb_line, int col_len);

// Function to get the map.
char	**get_map(t_cub3D *game, t_map *map, int start);

// A custome copy function to copy the map.
char	*ft_strncpy_2(char *dest, char *src, unsigned int n);

// Function to check is the character valid.
int		is_valid_element(t_cub3D *game, t_map *map, char c);

// Function that check and set the textures.
int		check_textures(t_cub3D *game, t_map *map, char *s, int flag);

// Function get the textures and colors from the map file.
int		get_basic_elements(t_cub3D *game, t_map *map);

// Function that check is the element is one of map one's.
int		one_of_map_elements(t_cub3D *game, t_map *map, char **s);

// Main function that checks and get map.
void	ft_check_map(t_cub3D *game, t_map *map, char *mapfile);

// Main function that contains all checks.
t_cub3D	*all_check(t_cub3D *game, char *mapfile);

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

// Function that add a pointer to the gc using a flag.
void	add_to_gc(t_cub3D *game, t_map *map, int flag);

// Function that free a double pointer.
void	free_double(char **s);

// Function that join two words and free the first one.
char	*freeing_join(char *s, char *s1);

// Function that clean cub3D.
void	clean_cub3D(t_cub3D *game);

/* Map */

void    render_square(t_cub3D *game, float x, float y, int color);

void    render_line(t_cub3D *game, int cx, int cy, int length, int color);

void    render_circle(t_cub3D *game, int cx, int cy, int radius, int color);

void    render_map_2(t_cub3D *game);

void    render_map(t_cub3D *game);

void    my_mlx_pixel_put(t_cub3D *game, float x, float y, int color);

int		is_walkable(t_cub3D *game, float new_x, float new_y);

void	update(t_cub3D *game);

void	reset(int keycode, t_cub3D *game);

int		ft_moving(int keycode, t_cub3D *game);

/* ************************************** */

void	castAllRays(t_cub3D *game);

void 	render_rays(t_cub3D *game);

float	normalize_angle(float x);

/* Printing */

void	ft_errors(t_cub3D *game, char *msg);

void	print_map_info(t_map *map);

int		ft_exit(t_cub3D *game);

#endif