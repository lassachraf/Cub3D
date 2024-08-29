/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:42:38 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/29 20:58:30 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long    deg_to_rad(long deg)
{
    return (deg * (PI / 180));
}

long    rad_to_deg(long rad)
{
    return (rad * (180 / PI));
}

long    distanceAB(int ax, int ay, int bx, int by)
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

/* ****************************************************** */

void render_ray(t_cub3D *game, float ray_angle, int color) {
    // Calculate the end position of the ray
    float end_x = game->player->x * TILE_SIZE + cos(ray_angle) * 30;
    float end_y = game->player->y * TILE_SIZE + sin(ray_angle) * 30;

    // Bresenham's line algorithm for drawing the ray
    long start_x = game->player->x * TILE_SIZE;
    long start_y = game->player->y * TILE_SIZE;
    long dx = labs((long)end_x - start_x), sx = start_x < end_x ? 1 : -1;
    long dy = -labs((long)end_y - start_y), sy = start_y < end_y ? 1 : -1;
    long err = dx + dy, e2;

    while (1) {
        // Draw the pixel at (start_x, start_y)
        my_mlx_pixel_put(game, start_x, start_y, color); // Draw with the specified color

        // Check if the line has reached the end point
        if (start_x == (long)end_x && start_y == (long)end_y) break;

        // Update error term and positions
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; start_x += sx; }
        if (e2 <= dx) { err += dx; start_y += sy; }
    }
}

void render_rays(t_cub3D *game) {
    float ray_angle = game->player->rotationangle - (game->fov_ang / 2);
    float step_angle = game->fov_ang / game->wov; // Calculate the angle step for each ray
    int i;

    // Render rays one by one to fill the FOV
    for (i = 0; i < game->wov; i++) {
        render_ray(game, ray_angle, 0x6600FF00); // Light green color with transparency
        ray_angle += step_angle; // Move to the next ray angle
    }
}

void	castAllRays(t_cub3D *game)
{
	t_rays	*rayzz;
	long	*rays;
	int	columnid = 0;
	float rayangle = game->player->rotationangle - (game->fov_ang / 2);

	int i = -1;
	rayzz = ft_malloc(game, sizeof(t_rays));
	rays = ft_malloc(game, (sizeof(long) * game->wov));
	while (++i < game->wov)
	{
		rays[i] = rayangle;
        rayangle += game->fov_ang / game->wov;
        columnid++;
	}
	rayzz->lst_of_rays = rays;
	game->rays = rayzz;
}

// void render_rays(t_cub3D *game)
// {
//     int i;

//     i = -1;
//     while (++i < game->wov)
//         render_ray(game, game->rays->lst_of_rays[i]);
// }

void	cub3D(t_cub3D *game)
{
	game->wov = game->map->width * TILE_SIZE;
	game->hov = game->map->height * TILE_SIZE;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->wov, game->wov,"Cub3D !");
	game->img = mlx_new_image(game->mlx, game->wov, game->wov);
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