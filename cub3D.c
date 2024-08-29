/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:42:38 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/29 15:43:17 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is_walkable(t_cub3D *game, double new_x, double new_y)
{
    int map_x = (int)new_x;
    int map_y = (int)new_y;

    if (map_x >= 0 && map_x < game->map->width && 
        map_y >= 0 && map_y < game->map->height && 
        game->map->map[map_y][map_x] != '1') {
        return (1);
    }
	printf("Not walkable !");
    return (0);
}

void	update(t_cub3D *game)
{
	float	new_x;
	float	new_y;
	float	movestep;

	movestep = game->player->walkdirection * game->player->movespeed;
	new_x = game->player->x + cos(game->player->rotationangle) * movestep;
	new_y = game->player->y + sin(game->player->rotationangle) * movestep;
	printf("new_x >> %f\n", new_x);
	if (is_walkable(game, new_x, new_y))
	{
		printf("Walkable\n");
		game->player->x = new_x;
		game->player->y = new_y;
	}
	game->player->rotationangle += game->player->turndirection * game->player->rotationspeed;
	printf("update !\n");
}

int	ft_exit(t_cub3D *game)
{
	clean_cub3D(game);
	exit(0);
}

void	reset(int keycode, t_cub3D *game)
{
	if (keycode == LEFT_ARROW)
		game->player->turndirection = 0;
	else if (keycode == UP_ARROW)
		game->player->walkdirection = 0;
	else if (keycode == RIGHT_ARROW)
		game->player->turndirection = 0;
	else if (keycode == DOWN_ARROW)
		game->player->walkdirection = 0;
}

int	ft_moving(int keycode, t_cub3D *game)
{
	if (keycode == ESC_KEY)
		ft_exit(game);
	else if (keycode == LEFT_ARROW)
		game->player->turndirection = -1;
	else if (keycode == UP_ARROW)
		game->player->walkdirection = 1;
	else if (keycode == RIGHT_ARROW)
		game->player->turndirection = 1;
	else if (keycode == DOWN_ARROW)
		game->player->walkdirection = -1;
	update(game);
	// render();
	reset(keycode, game);
	render_map_2(game);
	return (0);
}

void	ft_errors(t_cub3D *game, char *msg)
{
	printf(RED"%s\n"RESET, msg);
	if (game)
		gc_free_all(game);
	exit(1);
}

void	print_map_info(t_map *map)
{
	char	**s;
	int		i;

	i = 0;
	printf("/* Map infos after check */\n");
	printf("/* ceil  > %d */\n", map->ceil);
	printf("/* east  > %s */\n", map->east);
	printf("/* west  > %s */\n", map->west);
	printf("/* north > %s */\n", map->north);
	printf("/* floor > %d */\n", map->floor);
	printf("/* south > %s */\n", map->south);
	s = map->map;
	printf("/* --------------- MAP --------------- */\n");
	while (s[i])
	{
		printf("|*%s*|\n", s[i]);
		i++;
	}
	printf("/* --------------- MAP --------------- */\n");
}

void    my_mlx_pixel_put(t_cub3D *game, float x, float y, int color)
{
	if (x < 0 || y < 0 || x >= game->map->width * TILE_SIZE || y >= game->map->height * TILE_SIZE) 
        return ;
    char    *dst;

    dst = game->addr + (int)(y * game->szl + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void    render_square(t_cub3D *game, float x, float y, int color)
{
    int i, j;
    int square_size = TILE_SIZE;

    for (i = 0; i < square_size; i++)
    {
        for (j = 0; j < square_size; j++)
        {
            my_mlx_pixel_put(game, x + i, y + j, color);
        }
    }
}

void    render_line(t_cub3D *game, int cx, int cy, int length, int color)
{
	long end_x = cx + cos(game->player->rotationangle) * length;
	long end_y = cy + sin(game->player->rotationangle) * length;

	// printf("Render Line: Start (%d, %d), End (%ld, %ld), Angle: %f\n", cx, cy, end_x, end_y, game->player->rotationangle);
    long dx = labs(end_x - cx), sx = cx < end_x ? 1 : -1;
    long dy = -labs(end_y - cy), sy = cy < end_y ? 1 : -1;
    long err = dx + dy, e2;

    while (1)
    {
        my_mlx_pixel_put(game, cx, cy, color);
        if (cx == end_x && cy == end_y) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; cx += sx; }
        if (e2 <= dx) { err += dx; cy += sy; }
    }
}

void    render_circle(t_cub3D *game, int cx, int cy, int radius, int color)
{
    int x, y;

    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put(game, cx + x, cy + y, color);
            }
        }
    }
}

void    render_map_2(t_cub3D *game)
{
    int x, y;
    int color;

    y = -1;
	color = 0;
	while (game->map->map[++y])
    {
		x = -1;
        while (game->map->map[y][++x])
        {
            if (game->map->map[y][x] == '1')
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x00FF0000);
            else if (game->map->map[y][x] == 'D')
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x000000FF);
			else if (game->map->map[y][x] == ' ')
				render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x0000);
			else
			{
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x00CCCCCC);
            	render_circle(game, (game->player->x * TILE_SIZE), (game->player->y * TILE_SIZE), 6, 0x0099FFFF);
				render_line(game, (game->player->x * TILE_SIZE), (game->player->y * TILE_SIZE), 6 * 3, 0x0099FFFF);
			}
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void    render_map(t_cub3D *game)
{
    int x, y;
    int color;

    y = -1;
	color = 0;
	while (game->map->map[++y])
    {
		x = -1;
        while (game->map->map[y][++x])
        {
            if (game->map->map[y][x] == '1')
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x00FF0000);
            else if (game->map->map[y][x] == 'D')
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x000000FF);
			else if (game->map->map[y][x] == ' ')
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x0000);
            else
			{
				// printf("1 :: x >> %d, y >> %d, char > %c\n", x, y, game->map->map[y][x]);
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x00CCCCCC);
			}
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	cub3D(t_cub3D *game)
{
	int	x;
	int	y;

	x = game->map->width * TILE_SIZE;
	y = game->map->height * TILE_SIZE;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, x, y,"Cub3D !");
	game->img = mlx_new_image(game->mlx, x, y);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->szl, &game->end);
	render_map(game);
	mlx_hook(game->win, 2, 1L << 0, ft_moving, game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_cub3D	*game;
	t_gc	*gc;

	gc = NULL;
	game = NULL;
	if (ac != 2)
		ft_errors(NULL, "Arg Error : Expected 2 args.");
	game = (t_cub3D *)malloc(sizeof(t_cub3D));
	if (!game)
		ft_errors(NULL, "Allocation failed.");
	ft_bzero(game, (sizeof(t_cub3D)));
	gc = (t_gc *)malloc(sizeof(t_gc));
	if (!gc)
		ft_errors(NULL, "Allocation failed.");
	ft_bzero(gc, (sizeof(t_gc)));
	game->gc = gc;
	game = all_check(game, av[1]);
	cub3D(game);
	clean_cub3D(game);
	return (0);
}

// Things maybe used later :

// const angle = 60 * (PI * 180)

// const num_rays = length_of_view;

// rayAngle += angle / num_rays; 