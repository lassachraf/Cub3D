/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:58:16 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/14 18:42:15 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_exit(t_cub3D *game)
{
	clean_cub3D(game);
	exit(0);
}

void	cub3D(t_cub3D *game)
{
	int	x;
	int	y;

	x = game->map->width * TILE_SIZE;
	y = game->map->height * TILE_SIZE;
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

	game = NULL;
	if (ac != 2)
		ft_errors(NULL, "Arg Error : Expected 2 args.");
	game = (t_cub3D *)malloc(sizeof(t_cub3D));
	if (!game)
		ft_errors(NULL, "Allocation failed.");
	ft_bzero(game, (sizeof(t_cub3D)));
	game = parsing(game, av[1]);
	printf("** parsing jamil **\n");
	clean_cub3D(game);
	return (0);
}
