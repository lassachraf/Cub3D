/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:42:45 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/06 12:49:50 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
				render_circle(game, (game->player->x * TILE_SIZE), (game->player->y * TILE_SIZE), 3, 0x0099FFFF);
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
				render_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x00CCCCCC);
				render_circle(game, (game->player->x * TILE_SIZE), (game->player->y * TILE_SIZE), 3, 0x0099FFFF);
				render_rays(game);
			}
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
