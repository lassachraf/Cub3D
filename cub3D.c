/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:42:38 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/02 02:18:17 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long	deg_to_rad(long deg)
{
	return (deg * (PI / 180));
}

long	rad_to_deg(long rad)
{
	return (rad * (180 / PI));
}

long	twopointsdistance(int ax, int ay, int bx, int by)
{
	return (sqrt(pow((bx - ax), 2) + pow((by - ay), 2)));
}

int	ft_exit(t_cub3D *game)
{
	clean_cub3D(game);
	exit(0);
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

/* Find grid intersection */

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

float	*find_walls(t_cub3D *game, int *x, int *y, int id)
{
	float	*hit_point;
	float	nextxtouch;
	float	nextytouch;

	nextxtouch = x[0];
	nextytouch = y[0];
	if (game->rays->lst_of_rays[id].facing_up)
		nextxtouch--;
	while (nextxtouch >= 0 && nextxtouch <= game->wov
		&& nextytouch >= 0 && nextytouch <= game->hov)
	{
		if (!is_walkable(game, nextxtouch, nextytouch))
			break;
		else
		{
			nextxtouch += x[1];			
			nextytouch += y[1];
		}
	}
	hit_point = ft_malloc(game, sizeof(float) * 2);
	hit_point[0] = nextxtouch;
	hit_point[1] = nextytouch;
	render_line(game, nextxtouch, nextytouch, 7, 0x000000FF);
	return (hit_point);
}

void	cast(t_cub3D *game, int id)
{
	int		*x_list;
	int		*y_list;
	float	*hit_point;

	x_list = ft_malloc(game, sizeof(int) * 2);
	y_list = ft_malloc(game, sizeof(int) * 2);
	y_list[0] = get_y_index(game->player->y);
	if (game->rays->lst_of_rays[id].facing_down)
		y_list[0] += TILE_SIZE;
	x_list[0] = get_x_index(game, game->player->y, y_list[0], id);
	y_list[1] = TILE_SIZE;
	if (game->rays->lst_of_rays[id].facing_up)
		y_list[1] = TILE_SIZE * -1;
	x_list[1] = (int)(y_list[1] / tan(game->rays->lst_of_rays[id].ray_angle));
	if (game->rays->lst_of_rays[id].facing_left && x_list[1] > 0)
		x_list[1] *= -1;
	if (game->rays->lst_of_rays[id].facing_right && x_list[1] < 0)
		x_list[1] *= -1;
	hit_point = find_walls(game, x_list, y_list, id);
}


/* Rayssssssssssssssssssssss */

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
	while (++i < game->wov)
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

void	cub3D(t_cub3D *game)
{
	int x = game->map->width * TILE_SIZE;
	int y = game->map->height * TILE_SIZE;
	game->wov = x;
	game->hov = y;
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
	game->fov_ang = deg_to_rad(60);
	cub3D(game);
	clean_cub3D(game);
	return (0);
}

// Things maybe used later :

// const angle = 60 * (PI * 180)

// const num_rays = length_of_view;

// rayAngle += angle / num_rays; 