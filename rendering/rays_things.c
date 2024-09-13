/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:51:57 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/11 11:22:51 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

int	get_y_index(float y)
{
	return ((int)((y / TILE_SIZE) * TILE_SIZE));
}

int	get_x_index(t_cub3D *game, float y, float yint, int id)
{
	float	x;

	x = (y - yint) / tan(game->rays->lst_of_rays[id].ray_angle);
	return ((int)(game->player->x + x));
}

float	*find_walls(t_cub3D *game, float *x, float *y, int id)
{
	float	*hit_point;
	float	nextxtouch;
	float	nextytouch;

	hit_point = 0;
	nextxtouch = x[0];
	nextytouch = y[0];
	if (game->rays->lst_of_rays[id].facing_up)
		nextxtouch--;
	while (nextxtouch >= 0 && nextxtouch <= game->wov
		&& nextytouch >= 0 && nextytouch <= game->hov)
	{
		if (!is_walkable(game, nextxtouch, nextytouch))
		{
			hit_point = ft_malloc(game, sizeof(float) * 2);
			hit_point[0] = nextxtouch;
			hit_point[1] = nextytouch;
			render_line(game, nextxtouch, nextytouch, 10, 0x0033FF00);
			break;
		}
		else
		{
			nextxtouch += x[1];			
			nextytouch += y[1];
		}
	}
	return (hit_point);
}

void	cast(t_cub3D *game, int id)
{
	float	*x_list;
	float	*y_list;
	float	*hit_point;

	x_list = ft_malloc(game, sizeof(float) * 2);
	y_list = ft_malloc(game, sizeof(float) * 2);
	y_list[0] = (float)get_y_index(game->player->y);
	if (game->rays->lst_of_rays[id].facing_down)
		y_list[0] += TILE_SIZE;
	x_list[0] = (float)get_x_index(game, game->player->y, y_list[0], id);
	y_list[1] = TILE_SIZE;
	if (game->rays->lst_of_rays[id].facing_up)
		y_list[1] = TILE_SIZE * -1;
	x_list[1] = TILE_SIZE / tan(game->rays->lst_of_rays[id].ray_angle);
	if (game->rays->lst_of_rays[id].facing_left && x_list[1] > 0)
		x_list[1] *= -1;
	if (game->rays->lst_of_rays[id].facing_right && x_list[1] < 0)
		x_list[1] *= -1;
	hit_point = find_walls(game, x_list, y_list, id);
	// if (hit_point && hit_point[0] && hit_point[1])
	// 	printf("** finding walls : (%f, %f) ! **\n", hit_point[0], hit_point[1]);
}

void	render_ray(t_cub3D *game, float ray_angle, int color)
{
	float end_x = game->player->x * TILE_SIZE + cos(ray_angle) * 30;
	float end_y = game->player->y * TILE_SIZE + sin(ray_angle) * 30;
	long start_x = game->player->x * TILE_SIZE;
	long start_y = game->player->y * TILE_SIZE;
	long dx = labs((long)end_x - start_x), sx = start_x < end_x ? 1 : -1;
	long dy = -labs((long)end_y - start_y), sy = start_y < end_y ? 1 : -1;
	long err = dx + dy, e2;

	while (1)
	{
		my_mlx_pixel_put(game, start_x, start_y, color);
		if (start_x == (long)end_x && start_y == (long)end_y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			start_x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			start_y += sy;
		}
	}
}

void render_rays(t_cub3D *game)
{
	float	ray_angle;
	float	step_angle;
	int		i;

	i = -1;
	ray_angle = game->player->rotationangle - (game->fov_ang / 2);
	step_angle = game->fov_ang / game->wov;
	while (++i < 1)
	{
		render_ray(game, ray_angle, 0x6600FF00);
		ray_angle += step_angle;
	}
}

int	facingdown(t_cub3D *game, int id)
{
	float	x;

	x = game->rays->lst_of_rays[id].ray_angle;
	return (x > 0 && x < PI);
}

int	facingright(t_cub3D *game, int id)
{
	float	x;

	x = game->rays->lst_of_rays[id].ray_angle;
	return (x < (0.5 * PI) || x > (1.5 * PI));
}

void	castAllRays(t_cub3D *game)
{
	int		columnid;
	float	rayangle;
	int		i;

	i = -1;
	columnid = 0;
	game->rays = ft_malloc(game, sizeof(t_rays) * game->wov);
	game->rays->lst_of_rays = ft_malloc(game, sizeof(t_ray) * game->wov);
	rayangle = game->player->rotationangle - (game->fov_ang / 2);
	while (++i < game->wov)
	{
		game->rays->lst_of_rays[i].ray_angle = normalize_angle(rayangle);
		game->rays->lst_of_rays[i].distance = 0;
		game->rays->lst_of_rays[i].wall_hit_x = 0;
		game->rays->lst_of_rays[i].wall_hit_y = 0;
		game->rays->lst_of_rays[i].facing_up = !facingdown(game, i);
		game->rays->lst_of_rays[i].facing_down = facingdown(game, i);
		game->rays->lst_of_rays[i].facing_right = facingright(game, i);
		game->rays->lst_of_rays[i].facing_left = !facingright(game, i);
		// cast(game, columnid);
		rayangle += game->fov_ang / game->wov;
		columnid++;
	}
}
