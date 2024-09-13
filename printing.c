/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:49:42 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/06 12:37:47 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_double(char **dbl)
{
	size_t i = 0;
	size_t l = 0;

	while (dbl[i])
	{
		printf("%ld=\"%s\"\n", l, dbl[i]);
		l++;
		i++;
	}	
}

void	ft_errors(t_cub3D *game, char *msg)
{
	printf(RED"%s\n"RESET, msg);
	if (game)
		gc_free_all(game);
	exit(1);
}

void	print_player_info(t_player *player)
{
	printf("/* Player infos after check */\n");
	printf("/* x  > %f */\n", player->x);
	printf("/* y  > %f */\n", player->y);
	printf("/* count  > %d */\n", player->count);
	printf("/* radius > %ld */\n", player->radius);
	printf("/* movespeed  > %f */\n", player->movespeed);
	printf("/* rotationangle > %f */\n", player->rotationangle);
	printf("/* rotationspeed > %f */\n", player->rotationspeed);
	printf("/* turndirection > %d */\n", player->turndirection);
	printf("/* walkdirection > %d */\n", player->walkdirection);
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
	if (!s)
		printf("Empty map !\n");
	else
	{
		while (s[i])
		{
			printf("|*%s*|\n", s[i]);
			i++;
		}
	}
	printf("/* --------------- MAP --------------- */\n");
}
