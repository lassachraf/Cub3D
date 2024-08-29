/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:30:44 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/29 20:51:06 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    my_mlx_pixel_put(t_cub3D *game, float x, float y, int color)
{
	if (x < 0 || y < 0 || x >= game->map->width * TILE_SIZE || y >= game->map->height * TILE_SIZE) 
        return ;
    char    *dst;

    dst = game->addr + (int)(y * game->szl + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

int is_walkable(t_cub3D *game, double new_x, double new_y)
{
    int map_x = (int)new_x;
    int map_y = (int)new_y;

    if (map_x >= 0 && map_x < game->map->width && 
        map_y >= 0 && map_y < game->map->height && 
        game->map->map[map_y][map_x] != '1')
        return (1);
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
	if (is_walkable(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
	game->player->rotationangle += game->player->turndirection * game->player->rotationspeed;
	castAllRays(game);
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
	reset(keycode, game);
	render_map_2(game);
	render_rays(game);
	return (0);
}
