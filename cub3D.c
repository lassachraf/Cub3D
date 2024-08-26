/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:42:38 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/26 18:47:13 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_exit(t_cub3D *game)
{
	clean_cub3D(game);
	exit(0);
}

int	ft_esc(int keycode, t_cub3D *game)
{
	if (keycode == 65307)
		ft_exit(game);
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

void	update()
{
	// update all things that need to be updated;
	// change player position
}

void    my_mlx_pixel_put(t_cub3D *game, int x, int y, int color)
{
    char    *dst;

    dst = game->addr + (y * game->szl + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void    render_square(t_cub3D *game, int x, int y, int color)
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

void    render_line(t_cub3D *game, int cx, int cy, int length, int color, char direction)
{
    int end_x = cx, end_y = cy;

    if (direction == 'N') // North
        end_y -= length;
    else if (direction == 'S') // South
        end_y += length;
    else if (direction == 'W') // West
        end_x -= length;
    else if (direction == 'E') // East
        end_x += length;

    int dx = abs(end_x - cx), sx = cx < end_x ? 1 : -1;
    int dy = -abs(end_y - cy), sy = cy < end_y ? 1 : -1;
    int err = dx + dy, e2;

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
	// render_line(game, cx, cy, radius * 3, 0x0099FFFF, game->map->map[cy][cx]);
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
            else if (game->map->map[y][x] == '0')
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x00CCCCCC);
            else if (game->map->map[y][x] == 'D')
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x000000FF);
			else if (game->map->map[y][x] != ' ')
			{
                render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x00CCCCCC);
            	render_circle(game, x * TILE_SIZE, y * TILE_SIZE, 6, 0x0099FFFF);
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
	mlx_hook(game->win, 2, 1L << 0, ft_esc, game);
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